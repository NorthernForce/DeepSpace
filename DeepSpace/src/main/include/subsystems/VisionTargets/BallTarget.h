#pragma once

#include "subsystems/Vision.h"

class BallTarget : public Vision::Target {
 public:
  virtual void setup(Vision::Camera *camera) override;
  virtual void run(cv::Mat &frame) override;
  const std::string name = "Ball";
};