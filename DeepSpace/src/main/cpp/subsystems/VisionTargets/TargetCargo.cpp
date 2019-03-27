#include "subsystems/VisionTargets/TargetCargo.h"

#include <frc/smartdashboard/SmartDashboard.h>

const std::string TargetCargo::k_name = "Cargo";

const int TargetCargo::k_invertHue = 0;
const int TargetCargo::k_minHue = 35;
const int TargetCargo::k_maxHue = 85;
const int TargetCargo::k_minSat = 150;
const int TargetCargo::k_maxSat = 255;
const int TargetCargo::k_minVal = 115;
const int TargetCargo::k_maxVal = 255;

const double TargetCargo::k_minArea = 15;

TargetCargo::TargetCargo() {
  // Add smart dashboard stuff...
  frc::SmartDashboard::PutNumber("Vision: Cargo: HUE INVERT", k_invertHue);
  frc::SmartDashboard::PutNumber("Vision: Cargo: HUE MIN", k_invertHue);
  frc::SmartDashboard::PutNumber("Vision: Cargo: HUE MAX", k_maxHue);
  frc::SmartDashboard::PutNumber("Vision: Cargo: SAT MIN", k_minSat);
  frc::SmartDashboard::PutNumber("Vision: Cargo: SAT MAX", k_maxSat);
  frc::SmartDashboard::PutNumber("Vision: Cargo: VAL MIN", k_minVal);
  frc::SmartDashboard::PutNumber("Vision: Cargo: VAL MAX", k_maxVal);
}

void TargetCargo::setup(Vision::Camera *camera) {}

void TargetCargo::run(cv::Mat &frame) {

  cv::Mat filtered = frame.clone();

  // Attempt to remove some noise.
  cv::blur(filtered, filtered, cv::Size(3, 3));

  // Use HSV
  cv::cvtColor(filtered, filtered, cv::COLOR_BGR2HSV);

  // Gather values from the Smart Dashboard
  int invertHue = frc::SmartDashboard::GetNumber("Vision: Cargo: HUE INVERT", k_invertHue);
  int minHue = frc::SmartDashboard::GetNumber("Vision: Cargo: HUE MIN", k_minHue);
  int maxHue = frc::SmartDashboard::GetNumber("Vision: Cargo: HUE MAX", k_maxHue);
  int minSat = frc::SmartDashboard::GetNumber("Vision: Cargo: SAT MIN", k_minSat);
  int maxSat = frc::SmartDashboard::GetNumber("Vision: Cargo: SAT MAX", k_maxSat);
  int minVal = frc::SmartDashboard::GetNumber("Vision: Cargo: VAL MIN", k_minVal);
  int maxVal = frc::SmartDashboard::GetNumber("Vision: Cargo: VAL MAX", k_maxVal);
  
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
  cv::Moments largest;
  for (auto &contour : contours) {
    cv::Moments test = cv::moments(contour, false);

    // Test for minimum area and larger size.
    if (test.m00 >= k_minArea && test.m00 > largest.m00) {
        largest = test;
    }
  }

  // Return if no tapes were found
  if (largest.m00 == 0) {
    m_horizontalOffset = 0;
    m_verticalOffset = 0;
    return;
  }

  cv::Point center = cv::Point(largest.m10/largest.m00, largest.m01/largest.m00);

  // Debug
  cv::drawContours(frame, contours, -1, cv::Scalar(0, 255, 0));
  cv::circle(frame, center, 2, cv::Scalar(0, 255, 255), 2);

  // Convert to -1.0 to 1.0 where quadrant I is positive
  m_horizontalOffset = (center.x - frame.cols / 2.0) / (frame.cols / 2.0);
  m_verticalOffset = (center.y - frame.rows / 2.0) / (frame.rows / 2.0) * -1;
}