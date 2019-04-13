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
// TBD
const double Vision::ReflectiveTape::k_minArea = 15;

const double Vision::ReflectiveTape::k_maxFavoringAreaDiff = 0.2;
const double Vision::ReflectiveTape::k_maxFavoringCenterOffset = 2;
const double Vision::ReflectiveTape::k_maxSoftenerThreshold = 800;
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
        edge.angle = Utilities::CalcLineAngleDeg(poly[pointI], poly[pointI + 1]);

        edges.push_back(edge);

        cv::line(frame, poly[pointI], poly[pointI + 1], cv::Scalar(0, 0, 255));
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

    // Find each edge
    ReflectiveTapeBlob tape;
    for (auto& edge : edges) {
      switch ((int)((edge.angle + 45) / 90) % 4) {
      case 0: if (tape.bot.length < edge.length) tape.bot = edge; break;
      case 1: if (tape.right.length < edge.length) tape.right = edge; break;
      case 2: if (tape.top.length < edge.length) tape.top = edge; break;
      case 3: if (tape.left.length < edge.length) tape.left = edge; break;
      }
    }

    cv::circle(frame, tape.top.center, 1, cv::Scalar(100, 100, 0));
    cv::circle(frame, tape.left.center, 1, cv::Scalar(150, 150, 0));
    cv::circle(frame, tape.bot.center, 1, cv::Scalar(200, 200, 0));
    cv::circle(frame, tape.right.center, 1, cv::Scalar(250, 250, 255));
    
    // Calculate tape area
    double height;
    if (tape.right.length > tape.left.length) {
      height = tape.right.length * std::sin(tape.right.angle * 0.01745329251994);
    }
    else {
      height = tape.left.length * std::sin(tape.left.angle * 0.01745329251994);
    }
    double width = tape.right.center.x - tape.left.center.x;

    tape.area = std::abs(height * width);

    // std::cout << "area: " << tape.area << "\n";

    if (tape.area < k_minArea) {
      continue;
    }

    // Calculate tape type
    double botAdd = (tape.bot.length > 0) ? -(tape.bot.angle) : 0;
    double rightAdd = (tape.right.length > 0) ? (tape.right.angle - 90) : 0;
    double topAdd = (tape.top.length > 0) ? -(tape.top.angle - 180) : 0;
    double leftAdd = (tape.left.length > 0) ? (tape.left.angle - 270) : 0;

    double totalAngle = botAdd + rightAdd + topAdd + leftAdd;
    // double totalAngle = rightAdd + leftAdd;
    if (totalAngle < 0) {
      tape.isLeft = true;
      tape.center = tape.right.center;
    }
    else {
      tape.isLeft = false;
      tape.center = tape.left.center;
    }

    // Calculate better center
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

  // Define target areas and centers
  for (auto& target : targets) {
    // Total area is just addition of both areas
    target.area = target.left.area + target.right.area;

    if (target.right.area == 0) {
      // Don't use a single tape unless it doesn't touch a boundary
      //if (target.left.isOut) {
      	target.center = cv::Point(frame.cols / 2, frame.rows / 2);
      //}
      //else {
        // target.center = cv::Point(target.left.center);
      //}
    }
    else if (target.left.area == 0) {
      // Don't use a single tape unless it doesn't touch a boundary
      //if (target.right.isOut) {
      	target.center = cv::Point(frame.cols / 2, frame.rows / 2);
      //}
      //else {
        // target.center = cv::Point(target.right.center);
      //}
    }
  //	//else if (target.left.isOut || target.right.isOut) {
  //	//	// Use the raw center if either tape is out
  //	//	target.center = Utilities::CalcAvgPoint(target.right.center, target.left.center);;
  //	//}
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
      double softener = (k_maxSoftenerThreshold - target.area) / k_maxSoftenerThreshold;
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
  // cv::drawContours(frame, contours, -1, cv::Scalar(0, 255, 0));
  for (auto& target : targets) {
    cv::line(frame, target.left.center, target.right.center, cv::Scalar(255, 0, 0)); //blue line
    cv::circle(frame, target.left.center, 1, cv::Scalar(255, 0, 255)); // purple 
    cv::circle(frame, target.right.center, 1, cv::Scalar(255, 255, 0)); // teal circle
    cv::circle(frame, target.center, 1, cv::Scalar(255, 255, 255)); //white circle
  }
  cv::circle(frame, largestTarget.center, 1, cv::Scalar(0, 255, 255), 2); //yellow circle

  // Convert center to -1.0 to 1.0 where quadrant I is positive
  m_horizontalOffset = (largestTarget.center.x - frame.cols / 2.0) / (frame.cols / 2.0);
  m_verticalOffset = (largestTarget.center.y - frame.rows / 2.0) / (frame.rows / 2.0) * -1;
}
