#include "subsystems/Vision/Targets/ReflectiveTape.h"

#include "subsystems/Vision/Utilities.h"

#include <frc/smartdashboard/SmartDashboard.h>

const std::string Vision::ReflectiveTape::k_cameraSettings =
  "exposure_auto=1,"
  "exposure_absolute=5," // Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
  "white_balance_temperature_auto=0";

#define LIGHT_RING_COLOR_GREEN
#ifdef LIGHT_RING_COLOR_GREEN
const int Vision::ReflectiveTape::k_invertHue = 0;
const int Vision::ReflectiveTape::k_minHue = 55;
const int Vision::ReflectiveTape::k_maxHue = 80;
const int Vision::ReflectiveTape::k_minSat = 200;
const int Vision::ReflectiveTape::k_maxSat = 255;
const int Vision::ReflectiveTape::k_minVal = 50;
const int Vision::ReflectiveTape::k_maxVal = 255;
#else
const int Vision::ReflectiveTape::k_invertHue = 1;
const int Vision::ReflectiveTape::k_minHue = 20;
const int Vision::ReflectiveTape::k_maxHue = 160;
const int Vision::ReflectiveTape::k_minSat = 15;
const int Vision::ReflectiveTape::k_maxSat = 200;
const int Vision::ReflectiveTape::k_minVal = 150;
const int Vision::ReflectiveTape::k_maxVal = 255;
#endif

const double Vision::ReflectiveTape::k_polyAccuracy = 2;
const double Vision::ReflectiveTape::k_minLength = 4;
const double Vision::ReflectiveTape::k_maxHeightDiff = 0.15;

const double Vision::ReflectiveTape::k_minArea = 15;

const double Vision::ReflectiveTape::k_maxFavoringAreaDiff = 0.2;
const double Vision::ReflectiveTape::k_maxFavoringCenterOffset = 2;
const double Vision::ReflectiveTape::k_maxSoftenerThreshold = 750;
const double Vision::ReflectiveTape::k_maxFavoringBoundary = 0.3;

struct ReflectiveTapeEdge {
	cv::Point center;
	double length = 0;
	double angle = 0;
};

struct ReflectiveTapeBlob {
	ReflectiveTapeEdge top, right, bot, left;
	cv::Point center;
	double area = 0;
	bool isLeft;
};

struct ReflectiveTargetBlob {
	cv::Point center;
	ReflectiveTapeBlob left;
	ReflectiveTapeBlob right;
	double area = 0;
};

Vision::ReflectiveTape::ReflectiveTape() {
  k_name = "ReflectiveTape";

  // Add smart dashboard stuff...
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: HUE INVERT", k_invertHue);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: HUE MIN", k_minHue);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: HUE MAX", k_maxHue);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: SAT MIN", k_minSat);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: SAT MAX", k_maxSat);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: VAL MIN", k_minVal);
  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: VAL MAX", k_maxVal);

  frc::SmartDashboard::PutNumber("Vision: ReflectiveTape: MAX AREA", k_maxSoftenerThreshold);
}

void Vision::ReflectiveTape::setup(Vision::Camera *camera) {
  camera->updateSettings(k_cameraSettings);
  camera->setLightRing(true);
}

void Vision::ReflectiveTape::run(cv::Mat &frame) {
  cv::Mat filtered = frame.clone();

  // Attempt to remove some noise.
  cv::blur(filtered, filtered, cv::Size(3, 3));

  // Use HSV
  cv::cvtColor(filtered, filtered, cv::COLOR_BGR2HSV);

  // Gather values from the Smart Dashboard
  int invertHue = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: HUE INVERT", k_invertHue);
  int minHue = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: HUE MIN", k_minHue);
  int maxHue = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: HUE MAX", k_maxHue);
  int minSat = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: SAT MIN", k_minSat);
  int maxSat = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: SAT MAX", k_maxSat);
  int minVal = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: VAL MIN", k_minVal);
  int maxVal = frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: VAL MAX", k_maxVal);
  
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

  // Analyze the contours
  std::vector<ReflectiveTapeBlob> tapes;
  for (auto& contour : contours) {
    std::vector<cv::Point> poly;
    cv::approxPolyDP(contour, poly, k_polyAccuracy, true);
    poly.push_back(poly.front());

    std::vector<ReflectiveTapeEdge> edges;
    for (int pointI = 0; pointI < (poly.size() - 1); pointI++) {
      double length = Utilities::CalcLineLength(poly[pointI], poly[pointI + 1]);

      if (length > k_minLength) {
        ReflectiveTapeEdge edge;

        edge.length = length;
        edge.center = Utilities::CalcAvgPoint(poly[pointI], poly[pointI + 1]);
        edge.angle = Utilities::CalcLineAngle(poly[pointI], poly[pointI + 1]);

        edges.push_back(edge);

        cv::line(frame, poly[pointI], poly[pointI + 1], cv::Scalar(150, 150, 150));
      }
    }

    // Make sure enough edges are detected
    if (edges.size() < 2) {
      continue;
    }

    // Sort edges by size
    std::sort(edges.begin(), edges.end(),
      [](ReflectiveTapeEdge& a, ReflectiveTapeEdge& b) {
        return a.length > b.length;
      });

    // Create the tape
    ReflectiveTapeBlob tape;

    // Find each edge
    for (auto& edge : edges) {
      switch ((int)((edge.angle + Utilities::k_QuaterPi) / Utilities::k_HalfPi) % 4) {
      case 0: if (tape.bot.length < edge.length) tape.bot = edge; break;
      case 1: if (tape.right.length < edge.length) tape.right = edge; break;
      case 2: if (tape.top.length < edge.length) tape.top = edge; break;
      case 3: if (tape.left.length < edge.length) tape.left = edge; break;
      }
    }

    cv::circle(frame, tape.top.center, 1, cv::Scalar(255, 255, 0)); // cyan circle
    cv::circle(frame, tape.left.center, 1, cv::Scalar(0, 0, 255)); // red circle
    cv::circle(frame, tape.bot.center, 1, cv::Scalar(255, 0, 255)); // purple circle
    cv::circle(frame, tape.right.center, 1, cv::Scalar(0, 255, 0)); // green circle
    
    // // Calculate tape area (= largest edge length * approx width)
    // double height;
    // if (tape.right.length > tape.left.length) {
    //   height = tape.right.length * std::sin(tape.right.angle);
    // }
    // else {
    //   height = tape.left.length * std::sin(tape.left.angle);
    // }
    // double width = tape.right.center.x - tape.left.center.x;

    // double oldArea = std::abs(height * width);
    
    // Precisely calculate the tape area
    double xOffset = std::abs(tape.right.center.x - tape.left.center.x);
    double yOffset = std::abs(tape.right.center.y - tape.left.center.y);
    double length, theta;
    if (tape.right.length > tape.left.length) {
      length = tape.right.length;
      theta = tape.right.angle;
    }
    else {
      length = tape.left.length;
      theta = tape.left.angle - Utilities::k_Pi;
    }
    double hypotenuse = std::sqrt(std::pow(xOffset, 2) + std::pow(yOffset, 2));
    theta = std::atan2(yOffset, xOffset) - theta;
    double distance = hypotenuse * std::sin(theta);

    double newArea = std::abs(length * distance);

    // std::cout << "oldArea: " << oldArea << " newArea: " << newArea << "\n";

    // tape.area = oldArea;
    tape.area = newArea;

    if (tape.area < k_minArea) {
      continue;
    }

    // Calculate tape type using length as a factor
    // double botAdd = tape.bot.length * (tape.bot.angle) * -1;
    double rightAdd = tape.right.length * (tape.right.angle - Utilities::k_HalfPi * 1);
    // double topAdd = tape.top.length * (tape.top.angle - Utilities::k_HalfPi * 2) * -1;
    double leftAdd  = tape.left.length * (tape.left.angle - Utilities::k_HalfPi * 3);
    // double totalAngle = botAdd + rightAdd + topAdd + leftAdd;
    double totalAngle = rightAdd + leftAdd;
    
    if (totalAngle < 0) {
      tape.isLeft = true;
      tape.center = tape.right.center;
    }
    else {
      tape.isLeft = false;
      tape.center = tape.left.center;
    }

    // Calculate a fancy center
    // if (tape.left.length > tape.right.length) {
    //   if (tape.isLeft) {
    //     tape.center = cv::Point(tape.left.center.x, tape.right.center.y);
    //   }
    //   else {
    //     tape.center = tape.left.center;
    //   }
    // }
    // else {
    //   if (tape.isLeft) {
    //     tape.center = tape.right.center;
    //   }
    //   else {
    //     tape.center = cv::Point(tape.right.center.x, tape.left.center.y);
    //   }
    // }

    if (tape.isLeft) {
      tape.center = tape.right.center;
    }
    else {
      tape.center = tape.left.center;
    }

    tapes.push_back(tape);
  }

  // Return if no tapes were found
  if (tapes.empty()) {
    m_horizontalOffset = 0;
    m_verticalOffset = 0;
    return;
  }

  // Find largest tape
  auto largestTape = *std::max_element(tapes.begin(), tapes.end(),
    [](ReflectiveTapeBlob & a, ReflectiveTapeBlob & b) {
      return a.area < b.area;
    });

  // Sort tapes left to right
  std::sort(tapes.begin(), tapes.end(),
    [](ReflectiveTapeBlob & a, ReflectiveTapeBlob & b) {
      return a.center.x < b.center.x;
    });

  // Groups tapes into targets
  cv::Rect heightBound = cv::Rect(0, largestTape.center.y - frame.rows * k_maxHeightDiff, frame.cols, frame.rows * k_maxHeightDiff * 2);
  std::vector<ReflectiveTargetBlob> targets;
  for (auto& tape : tapes) {
    if (!heightBound.contains(tape.center)) {
      continue;
    }

    if (tape.isLeft) {
      if (targets.empty() || targets.back().right.area > 0) {
        // Creates a new target if all previous are complete
        ReflectiveTargetBlob target;
        target.left = tape;

        targets.push_back(target);
      }
      else if (targets.back().left.area < tape.area) {
        // Overrides previous tape if not complete and area is larger
        targets.back().left = tape;
      }
    }
    else {
      if (targets.empty()) {
        // If the first tape is right, it's alone
        ReflectiveTargetBlob target;
        target.right = tape;

        targets.push_back(target);
      }
      else if (targets.back().right.area < tape.area) {
        // Override the previous pair if new right tape is larger
        //if (tape.area > targets.back().left.area / k_maxAreaDiff) {
          // Only use the new tape if it is larger than half the left's area
          targets.back().right = tape;
        //}
      }
    }
  }

  double maxSoftenerThreshold =  frc::SmartDashboard::GetNumber("Vision: ReflectiveTape: MAX AREA", k_maxSoftenerThreshold);

  // Define target areas and centers
  for (auto& target : targets) {
    // Total area is just addition of both areas
    target.area = target.left.area + target.right.area;

    // std::cout << "totalArea: " << target.area << " leftArea: " << target.left.area << " rightArea: "  << target.right.area << "\n";

    if (target.right.area == 0) {
      if (target.area < maxSoftenerThreshold / 2) {
        target.center = cv::Point(target.left.center);
      }
      else {
        target.center = cv::Point(frame.cols / 2, frame.rows / 2);
      }
    }
    else if (target.left.area == 0) {
      if (target.area < maxSoftenerThreshold / 2) {
        target.center = cv::Point(frame.cols / 2, frame.rows / 2);
      }
      else {
        target.center = cv::Point(target.right.center);
      }
    }
    else {
      // Find offset severity based on tape areas
      double severity = (target.left.area / target.area - 0.5) / k_maxFavoringAreaDiff;
      if (severity < -1) {
        severity = -1;
      }
      else if (severity > 1) {
        severity = 1;
      }

      // Find the offset softener (larger area = less offset)
      double softener = (maxSoftenerThreshold - target.area) / maxSoftenerThreshold;
      if (softener < 0) {
        softener = 0;
      }

      // Calculate the true severity of the difference of areas
      severity *= softener * k_maxFavoringCenterOffset;

      cv::Point avgCenter = Utilities::CalcAvgPoint(target.left.center, target.right.center);
      int centerX = avgCenter.x;
      int centerY = avgCenter.y;

      cv::Rect boundary = cv::Rect(frame.cols * (0.5 - k_maxFavoringBoundary), 0, frame.cols * k_maxFavoringBoundary * 2, frame.rows - 1);
      if (boundary.contains(target.right.center) && boundary.contains(target.left.center)) {
        centerX += std::round(std::abs(target.right.center.x - target.left.center.x) * severity);
        centerY += std::round(std::abs(target.right.center.y - target.left.center.y) * severity);
      }

      target.center = cv::Point(centerX, centerY);
    }
  }

  if (targets.empty()) {
    m_horizontalOffset = 0;
    m_verticalOffset = 0;
    return;
  }

  // Find target with the greatest area
  auto largestTarget = *std::max_element(targets.begin(), targets.end(),
    [](ReflectiveTargetBlob& a, ReflectiveTargetBlob& b) {
      return a.area < b.area;
    });

  // Debugging
  // cv::drawContours(frame, contours, -1, cv::Scalar(200, 200, 200));
  for (auto& target : targets) {
    cv::line(frame, target.left.center, target.right.center, cv::Scalar(255, 0, 0)); // blue line

    cv::circle(frame, target.center, 1, cv::Scalar(0, 255, 255)); // yellow circle
  }
  cv::circle(frame, largestTarget.center, 1, cv::Scalar(255, 255, 255), 2); // white circle

  // Convert center to -1.0 to 1.0 where quadrant I is positive
  m_horizontalOffset = (largestTarget.center.x - frame.cols / 2.0) / (frame.cols / 2.0);
  m_verticalOffset = (largestTarget.center.y - frame.rows / 2.0) / (frame.rows / 2.0) * -1;
}
