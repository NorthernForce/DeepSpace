#include "subsystems/ComputerVisionTargets/TapeTarget.h"

const std::string TapeTarget::cameraSettingsCommand = ComputerVision::cameraSettingsBaseCommand +
  "exposure_auto=1,"
  "exposure_absolute=5" // Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
  "white_balance_temperature_auto=0";

void TapeTarget::setup() {
  // TODO: Turn on light ring

  system(TapeTarget::cameraSettingsCommand.c_str());
}

std::pair<double, double> TapeTarget::run(cv::Mat frame, std::shared_ptr<cs::CvSource> debug) {
  cv::Mat filtered = frame;

  // Attempt to remove some noise.
  cv::blur(filtered, filtered, cv::Size(3, 3));

  // // Use gray scale.
  // cv::cvtColor(filtered, filtered, cv::COLOR_BGR2GRAY);

  // // Threshold it.
  // cv::threshold(filtered, filtered, 50, 255, cv::THRESH_BINARY);

  // Use HSV.
  cv::cvtColor(filtered, filtered, cv::COLOR_BGR2HSV);

  // Try to threshold the tape.
  cv::inRange(filtered, k_minHSV, k_maxHSV, filtered);

  // // Get rid of spots.
  // cv::erode(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);
  // cv::dilate(filtered, filtered, cv::Mat(), cv::Point(-1, -1), 2);

  // Find contours.
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(filtered, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

  // Also find largest two contours
  cv::Moments first, second;
  for (int i = 0; i < contours.size(); i++) {
    cv::Moments test = cv::moments(contours[i], false);

    // Minimum area.
    if (test.m00 >= k_minArea) {
      if (first.m00 < test.m00) {
        second = first;
        first = test;
      }
      else if (second.m00 < test.m00) {
        second = test;
      }
    }
  }

  // Make sure two targets were found.
  if (second.m00 == 0) {
    return std::make_pair(0, 0);
  }

  double centerX = (first.m10/first.m00 + second.m10/second.m00) / 2;
  double centerY = (first.m01/first.m00 + second.m01/second.m00) / 2;

  // Debug
  if (debug != nullptr) {
    cv::Mat result = frame;
    cv::cvtColor(result, result, cv::COLOR_HSV2BGR);
    for (int i = 0; i < contours.size(); i++) {
      cv::drawContours(result, contours, i, cv::Scalar(0, 255, 0));
    }
    cv::circle(result, cv::Point(first.m10/first.m00, first.m01/first.m00), 1, cv::Scalar(255, 0, 0), 2);
    cv::circle(result, cv::Point(second.m10/second.m00, second.m01/second.m00), 1, cv::Scalar(255, 0, 0), 2);
    cv::circle(result, cv::Point(centerX, centerY), 1, cv::Scalar(0, 0, 255), 2);
    debug->PutFrame(result);

    // std::cout << "area1: " << first.m00 << " area2: " << second.m00 << "\n";
    // std::cout << "x: " << centerX << " y: " << centerY << "\n";
  }

  // Convert to decimals
  centerX = (frame.cols / 2 - centerX) / (frame.cols / 2);
  centerY = (frame.rows / 2 - centerY) / (frame.rows / 2);

  return std::make_pair(centerX, centerY);
}