#pragma once

#include "subsystems/Vision/Targets/Target.h"

namespace Vision {

class ReflectiveTape : public Target {
 public:
  ReflectiveTape();
  virtual void setup(Camera *camera) override;
  virtual void run(cv::Mat &frame) override;
  const static std::string k_name;

 private:
  const static std::string k_cameraSettings;

  const static int k_invertHue;
  const static int k_minHue, k_maxHue;
  const static int k_minSat, k_maxSat;
  const static int k_minVal, k_maxVal;

  const static double k_minArea;
  const static double k_maxAreaDiff;
  const static double k_maxCenterOffset;
};

}