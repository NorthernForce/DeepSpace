#pragma once

#include "subsystems/Vision.h"

class TargetReflectiveTape : public Vision::Target {
 public:
  TargetReflectiveTape();
  virtual void setup(Vision::Camera *camera) override;
  virtual void run(cv::Mat &frame) override;
  const static std::string k_name;

 private:
  const static std::string k_cameraSettings;

  const static cv::Scalar k_minHSV;
  const static cv::Scalar k_maxHSV;
  const static double k_minArea;
  const static double k_centerMassDistance;
  // const static double k_centerMassOffset;
};