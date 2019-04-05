#pragma once

#include "subsystems/Vision/Targets/Target.h"

namespace Vision {

class Cargo : public Target {
 public:
  Cargo();
  virtual void setup(Camera *camera) override;
  virtual void run(cv::Mat &frame) override;

 private:
  const static int k_invertHue;
  const static int k_minHue, k_maxHue;
  const static int k_minSat, k_maxSat;
  const static int k_minVal, k_maxVal;

  const static double k_minArea;
};

}