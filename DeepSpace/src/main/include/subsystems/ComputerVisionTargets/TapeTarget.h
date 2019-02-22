#pragma once

#include "subsystems/ComputerVision.h"

class TapeTarget: public ComputerVision::Target {
 public:
  virtual void setup(std::shared_ptr<cs::UsbCamera> camera) override;
  virtual std::pair<double, double> run(cv::Mat frame) override;
  const std::string name = "Tape";
};