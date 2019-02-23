#pragma once

#include "subsystems/ComputerVision.h"

class BallTarget: public ComputerVision::Target {
 public:
  virtual void setup() override;
  virtual std::pair<double, double> run(cv::Mat frame, std::shared_ptr<cs::CvSource> debug) override;
  const std::string name = "Ball";
};