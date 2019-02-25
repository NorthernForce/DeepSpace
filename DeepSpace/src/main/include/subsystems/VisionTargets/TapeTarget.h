#pragma once

#include "subsystems/Vision.h"

class TapeTarget : public Vision::Target {
 public:
  virtual void setup(Vision::Camera *camera) override;
  virtual void run(cv::Mat &frame) override;
  const std::string name = "Tape";

 private:
  const std::string k_cameraSettings =
    "exposure_auto=1,"
    "exposure_absolute=5," // Valid exposures are "5, 10, 20, 39, 78, 156, 312, 625, 1250, 2500, 5000, 10000, 20000"
    "white_balance_temperature_auto=0";

  const cv::Scalar k_minHSV = cv::Scalar(70, 100, 50);
  const cv::Scalar k_maxHSV = cv::Scalar(100, 255, 255);
  const double k_minArea = 15;
};