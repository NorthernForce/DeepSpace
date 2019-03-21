#include "subsystems/VisionTargets/TargetReflectiveTape.h"

#include <frc/smartdashboard/SmartDashboard.h>

const std::string TargetReflectiveTape::k_name = "ReflectiveTape";

const std::string TargetReflectiveTape::k_cameraSettings =
  "exposure_auto=1,"
  "exposure_absolute=5," // Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
  "white_balance_temperature_auto=0";

// Green:
// const cv::Scalar TargetReflectiveTape::k_minHSV = cv::Scalar(35, 150, 50);
// const cv::Scalar TargetReflectiveTape::k_maxHSV = cv::Scalar(90, 255, 255);
// Pink: (NOT)
const cv::Scalar TargetReflectiveTape::k_minHSV = cv::Scalar(0, 0, 230);
const cv::Scalar TargetReflectiveTape::k_maxHSV = cv::Scalar(180, 100, 255);
// const cv::Scalar TargetReflectiveTape::k_minHSV = cv::Scalar(160, 0, 150);
// const cv::Scalar TargetReflectiveTape::k_maxHSV = cv::Scalar(200, 100, 255);

const double TargetReflectiveTape::k_minArea = 15;

struct ReflectiveTape {
	cv::Point center;
	double area = 0;
	bool isLeft;
};

struct ReflectiveTarget {
	cv::Point center;
	ReflectiveTape leftTape;
	ReflectiveTape rightTape;
	double totalArea = 0;
};

TargetReflectiveTape::TargetReflectiveTape() {
  // Add smart dashboard stuff...
  frc::SmartDashboard::PutNumber("Vision: INVERT", 0);
  frc::SmartDashboard::PutNumber("Vision: H MIN", 0);
  frc::SmartDashboard::PutNumber("Vision: H MAX", 255);
  frc::SmartDashboard::PutNumber("Vision: S MIN", 0);
  frc::SmartDashboard::PutNumber("Vision: S MAX", 255);
  frc::SmartDashboard::PutNumber("Vision: V MIN", 0);
  frc::SmartDashboard::PutNumber("Vision: V MAX", 255);
}

void TargetReflectiveTape::setup(Vision::Camera *camera) {
  camera->updateSettings(k_cameraSettings);
  camera->setLightRing(true);
}

void TargetReflectiveTape::run(cv::Mat &frame) {
  cv::Mat filtered = frame.clone();

  // Attempt to remove some noise.
  cv::blur(filtered, filtered, cv::Size(3, 3));

  // Use HSV
  cv::cvtColor(filtered, filtered, cv::COLOR_BGR2HSV);

  // Try to threshold the tape
  int invert = frc::SmartDashboard::GetNumber("Vision: INVERT", 0);
  int hueMin = frc::SmartDashboard::GetNumber("Vision: HUE MIN", 0);
  int hueMax = frc::SmartDashboard::GetNumber("Vision: HUE MAX", 255);
  int satMin = frc::SmartDashboard::GetNumber("Vision: SAT MIN", 0);
  int satMax = frc::SmartDashboard::GetNumber("Vision: SAT MAX", 255);
  int valMin = frc::SmartDashboard::GetNumber("Vision: VAL MIN", 0);
  int valMax = frc::SmartDashboard::GetNumber("Vision: VAL MAX", 255);
  
  // cv::inRange(filtered, k_minHSV, k_maxHSV, filtered);
  cv::inRange(filtered, cv::Scalar(hueMin, satMin, valMin), cv::Scalar(hueMax, satMax, valMax), filtered);
  // If mask must be inverted try this:
  if (invert != 0) {
    cv::bitwise_not(filtered, filtered);
  }

  // frame = filtered.clone();

  // Get rid of spots.
  cv::erode(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);
  cv::dilate(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);

  // Find contours.
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(filtered, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

  // Analyze contours
  std::vector<ReflectiveTape> tapes;
  for (auto &contour : contours) {
    cv::Moments test = cv::moments(contour, false);

    // Test for minimum area.
    if (test.m00 >= k_minArea) {
      ReflectiveTape tape;
      tape.area = test.m00;
      tape.center = cv::Point(test.m10/test.m00, test.m01/test.m00);
      
      // Find furthest left and right points (extreme points)
      auto points = std::minmax_element(contour.begin(), contour.end(),
        [](cv::Point &a, cv::Point &b) {
          return a.x < b.x;
      });

      // Compares heights of extreme points to determine whether left or right
      if (points.first->y < points.second->y) {
        tape.isLeft = false;
      }
      else {
        tape.isLeft = true;
      }

      tapes.push_back(tape);
    }
  }

  // Return if not tapes were found
  if (tapes.empty()) {
    m_horizontalOffset = 0;
    m_verticalOffset = 0;
    return;
  }

  // Sort tapes left to right
  std::sort(tapes.begin(), tapes.end(),
    [](ReflectiveTape &a, ReflectiveTape &b) {
      return a.center.x < b.center.x;
  });

  // Groups tapes into targets
  std::vector<ReflectiveTarget> targets;
  for (auto &tape : tapes) {
    if (tape.isLeft) {
      if (targets.empty() || targets.back().rightTape.area > 0) {
        // Creates a new target if all previous are complete
        ReflectiveTarget target;
        target.leftTape = tape;

        targets.push_back(target);
      }
      else if (targets.back().leftTape.area < tape.area) {
        // Overrides previous tape if not complete and area is larger
        targets.back().leftTape = tape;
      }
    }
    else {
      if (targets.empty()) {
        // If the first tape is right, it's alone
        ReflectiveTarget target;
        target.rightTape = tape;

        targets.push_back(target);
      }
      else if (targets.back().rightTape.area < tape.area) {
        // Override the previous pair if new right tape is larger
        targets.back().rightTape = tape;
      }
    }
  }

  // Define target areas and centers
  for (auto &target : targets) {
    // Only use average center if both tapes are found
    if (target.leftTape.area > 0 && target.rightTape.area == 0) {
      target.center = target.leftTape.center;
    }
    else if (target.leftTape.area == 0 && target.rightTape.area > 0) {
      target.center = target.rightTape.center;
    }
    else if (target.leftTape.area > 0 && target.rightTape.area > 0) {
      target.center = cv::Point((target.leftTape.center.x + target.rightTape.center.x) / 2,
                    (target.leftTape.center.y + target.rightTape.center.y) / 2);
    }

    // Total area is just addition of taoe areas
    target.totalArea = target.leftTape.area + target.rightTape.area;
  }

  // Find target with the greatest area
  auto largestTarget = *std::max_element(targets.begin(), targets.end(),
    [](ReflectiveTarget &a, ReflectiveTarget &b) {
      return a.totalArea < b.totalArea;
  });

  // Debug
  cv::drawContours(frame, contours, -1, cv::Scalar(0, 255, 0));
  for (auto &target : targets) {
    cv::line(frame, target.leftTape.center, target.rightTape.center, cv::Scalar(255, 0, 0));
    cv::circle(frame, target.center, 1, cv::Scalar(0, 0, 255), 2);
  }
  cv::circle(frame, largestTarget.center, 2, cv::Scalar(0, 255, 255), 2);

  // Convert to -1.0 to 1.0 where quadrant I is positive
  m_horizontalOffset = (largestTarget.center.x - frame.cols / 2.0) / (frame.cols / 2.0);
  m_verticalOffset = (largestTarget.center.y - frame.rows / 2.0) / (frame.rows / 2.0) * -1;

  std::cout << "m_horizontalOffset: " << m_horizontalOffset.load() << " m_verticalOffset: " << m_verticalOffset.load() << "\n";
}
