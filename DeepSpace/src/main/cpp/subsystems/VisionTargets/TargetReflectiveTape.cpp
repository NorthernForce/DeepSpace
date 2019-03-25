#include "subsystems/VisionTargets/TargetReflectiveTape.h"

#include <frc/smartdashboard/SmartDashboard.h>

const std::string TargetReflectiveTape::k_name = "ReflectiveTape";

const std::string TargetReflectiveTape::k_cameraSettings =
  "exposure_auto=1,"
  "exposure_absolute=5," // Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
  "white_balance_temperature_auto=0";

#define LIGHT_RING_COLOR_GREEN
#ifdef LIGHT_RING_COLOR_GREEN
const int TargetReflectiveTape::k_invertHue = 0;
const int TargetReflectiveTape::k_minHue = 35;
const int TargetReflectiveTape::k_maxHue = 85;
const int TargetReflectiveTape::k_minSat = 150;
const int TargetReflectiveTape::k_maxSat = 255;
const int TargetReflectiveTape::k_minVal = 115;
const int TargetReflectiveTape::k_maxVal = 255;
#else
const int TargetReflectiveTape::k_invertHue = 1;
const int TargetReflectiveTape::k_minHue = 20;
const int TargetReflectiveTape::k_maxHue = 160;
const int TargetReflectiveTape::k_minSat = 15;
const int TargetReflectiveTape::k_maxSat = 200;
const int TargetReflectiveTape::k_minVal = 150;
const int TargetReflectiveTape::k_maxVal = 255;
#endif

const double TargetReflectiveTape::k_minArea = 15;

const double TargetReflectiveTape::k_maxAreaDiff = 0.1;
const double TargetReflectiveTape::k_maxCenterOffset = 0.15;

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
  frc::SmartDashboard::PutNumber("Vision: HUE INVERT", k_invertHue);
  frc::SmartDashboard::PutNumber("Vision: HUE MIN", k_minHue);
  frc::SmartDashboard::PutNumber("Vision: HUE MAX", k_maxHue);
  frc::SmartDashboard::PutNumber("Vision: SAT MIN", k_minSat);
  frc::SmartDashboard::PutNumber("Vision: SAT MAX", k_maxSat);
  frc::SmartDashboard::PutNumber("Vision: VAL MIN", k_minVal);
  frc::SmartDashboard::PutNumber("Vision: VAL MAX", k_maxVal);
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

  // Gather values from the Smart Dashboard
  int invertHue = frc::SmartDashboard::GetNumber("Vision: HUE INVERT", k_invertHue);
  int minHue = frc::SmartDashboard::GetNumber("Vision: HUE MIN", k_minHue);
  int maxHue = frc::SmartDashboard::GetNumber("Vision: HUE MAX", k_maxHue);
  int minSat = frc::SmartDashboard::GetNumber("Vision: SAT MIN", k_minSat);
  int maxSat = frc::SmartDashboard::GetNumber("Vision: SAT MAX", k_maxSat);
  int minVal = frc::SmartDashboard::GetNumber("Vision: VAL MIN", k_minVal);
  int maxVal = frc::SmartDashboard::GetNumber("Vision: VAL MAX", k_maxVal);
  
  // Threshold the image
  if (invertHue == 0) {
    cv::inRange(filtered, cv::Scalar(minHue, minSat, minVal), cv::Scalar(maxHue, maxSat, maxVal), filtered);
  }
  else {
    cv::Mat lower, upper;
    cv::inRange(filtered, cv::Scalar(0, minSat, minVal), cv::Scalar(minHue, maxSat, maxVal), lower);
    cv::inRange(filtered, cv::Scalar(maxHue, minSat, minVal), cv::Scalar(180, maxSat, maxVal), upper);
    cv::bitwise_or(lower, upper, filtered);
  }

  // For debugging show the bitmap on the smartdashboard
  // frame = filtered.clone();

  // Get rid of spots.
  // cv::erode(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);
  // cv::dilate(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);

  // Find contours.
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(filtered, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

  // Analyze the contours (as tapes)
  std::vector<ReflectiveTape> tapes;
  for (auto &contour : contours) {
    cv::Moments test = cv::moments(contour, false);

    // Test for minimum area.
    if (test.m00 >= k_minArea) {
      ReflectiveTape tape;
      tape.area = test.m00;
      tape.center = cv::Point(test.m10/test.m00, test.m01/test.m00);
      
      // Find furthest left and right points (extreme points).
      // auto points = std::minmax_element(contour.begin(), contour.end(),
      //   [](cv::Point &a, cv::Point &b) {
      //     return a.x < b.x;
      // });

      // Finds the average of the leftest and rightest points (extreme points)
      cv::Point leftTop = contour[0], leftBot = contour[0], rightTop = contour[0], rightBot = contour[0];
      for (auto &point : contour) {
        if (point.x < leftTop.x) {
          leftTop = point;
          leftBot = point;
        }
        else if (point.x == leftTop.x) {
          if (point.y < leftTop.y) {
            leftTop = point;
          }
          else if (point.y > leftBot.y) {
            leftBot = point;
          }
        }
        else if (point.x > rightTop.x) {
          rightTop = point;
          rightBot = point;
        }
        else if (point.x == rightTop.x) {
          if (point.y < rightTop.y) {
            rightTop = point;
          }
          else if (point.y > rightBot.y) {
            rightBot = point;
          }
        }
      }

      // Compares heights of extreme points to determine whether left or right
      if ((leftTop.y + leftBot.y) / 2 < (rightTop.y + rightTop.y) / 2) {
        tape.isLeft = false;
      }
      else {
        tape.isLeft = true;
      }

      tapes.push_back(tape);
    }
  }

  // Return if no tapes were found
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
    // Total area is just addition of taoe areas
    target.totalArea = target.leftTape.area + target.rightTape.area;

    // Only use average center if both tapes are found
    if (target.rightTape.area == 0) {
      target.center = target.leftTape.center;
    }
    else if (target.leftTape.area == 0) {
      target.center = target.rightTape.center;
    }
    else {
      // // Calculate raw average point
      // target.center = cv::Point((target.leftTape.center.x + target.rightTape.center.x) / 2,
      //               (target.leftTape.center.y + target.rightTape.center.y) / 2);

      // Scale the point based on the size of the seperate tapes
      double severity = (target.leftTape.area / target.totalArea - 0.5) / k_maxAreaDiff;

      if (severity < -1) {
        severity = -1;
      }
      else if (severity > 1) {
        severity = 1;
      }

      severity *= k_maxCenterOffset;

      int centerX = (target.leftTape.center.x + target.rightTape.center.x) / 2 + (target.rightTape.center.x - target.leftTape.center.x) * severity;
      int centerY = (target.leftTape.center.y + target.rightTape.center.y) / 2 + (target.rightTape.center.y - target.leftTape.center.y) * severity;

      target.center = cv::Point(centerX, centerY);
    }
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

  // std::cout << "m_horizontalOffset: " << m_horizontalOffset.load() << " m_verticalOffset: " << m_verticalOffset.load() << "\n";
  // std::cout << "percentage: " << (largestTarget.leftTape.area / largestTarget.totalArea) << "\n";
  std::cout << "leftArea: " << largestTarget.leftTape.area;
  std::cout << " rightArea: " << largestTarget.rightTape.area;
  std::cout << " distance: " << std::sqrt(std::pow(largestTarget.rightTape.center.x - largestTarget.leftTape.center.x, 2) + std::pow(largestTarget.rightTape.center.y - largestTarget.leftTape.center.y, 2)) << "\n";
}
