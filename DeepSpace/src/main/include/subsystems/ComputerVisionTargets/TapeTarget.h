#pragma once

#include "subsystems/ComputerVision.h"

class TapeTarget: public ComputerVision::Target {
 public:
  virtual void setup() override;
  virtual std::pair<double, double> run(cv::Mat frame, std::shared_ptr<cs::CvSource> debug) override;
  const std::string name = "Tape";

  static const std::string cameraSettingsCommand;

 private:
  const cv::Scalar k_minHSV = cv::Scalar(70, 100, 50);
  const cv::Scalar k_maxHSV = cv::Scalar(100, 255, 255);
  const double k_minArea = 15;
};