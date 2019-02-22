#include "subsystems/ComputerVisionTargets/TapeTarget.h"

void TapeTarget::setup(std::shared_ptr<cs::UsbCamera> camera) {
  /*
   * Must run "opkg install v4l-utils" on the roborio whilst connected to
   * the internet (e.g. by ethernet)
   * 
   * Also, use -l to list the controls
   *     - Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
   */

  // system("v4l2-ctl -d 2 -c exposure_auto=1,exposure_absolute=10");
}

std::pair<double, double> TapeTarget::run(cv::Mat frame) {
  cv::Mat filtered = frame;

  // Attempt to remove some noise.
  cv::blur(filtered, filtered, cv::Size(3, 3));

  // Use gray scale.
  cv::cvtColor(filtered, filtered, cv::COLOR_BGR2GRAY);

  // Threshold it.
  cv::threshold(filtered, filtered, 100, 255, cv::THRESH_BINARY);

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

    if (first.m00 < test.m00) {
      second = first;
      first = test;
    }
    else if (second.m00 < test.m00) {
      second = test;
    }
  }

  double centerX = (first.m10/first.m00 + second.m10/second.m00) / 2;
  double centerY = (first.m01/first.m00 + second.m01/second.m00) / 2;

  // Debug
  cs::CvSource resultSource = frc::CameraServer::GetInstance()->PutVideo("TapeTarget Result", frame.rows, frame.cols);
  cv::Mat result = frame;
  for (int i = 0; i < contours.size(); i++) {
    cv::drawContours(result, contours, i, cv::Scalar(0, 255, 0));
  }
  cv::circle(result, cv::Point(first.m10/first.m00, first.m01/first.m00), 1, cv::Scalar(255, 0, 0), 2);
  cv::circle(result, cv::Point(second.m10/second.m00, second.m01/second.m00), 1, cv::Scalar(255, 0, 0), 2);
  cv::circle(result, cv::Point(centerX, centerY), 1, cv::Scalar(0, 0, 255), 2);
  resultSource.PutFrame(result);

  // Convert to decimals
  centerX = (frame.rows / 2 - centerX) / (frame.rows / 2);
  centerY = (frame.cols / 2 - centerY) / (frame.cols / 2);

  std::cout << "x: " << centerX << " y: " << centerY << "\n";

  return std::make_pair(centerX, centerY);
}