#pragma once

#include "subsystems/Vision.h"

class TargetCargo : public Vision::Target {
 public:
  TargetCargo();
  virtual void setup(Vision::Camera *camera) override;
  virtual void run(cv::Mat &frame) override;
  const static std::string k_name;

 private:
  const static int k_invertHue;
  const static int k_minHue, k_maxHue;
  const static int k_minSat, k_maxSat;
  const static int k_minVal, k_maxVal;

  const static double k_minArea;
};