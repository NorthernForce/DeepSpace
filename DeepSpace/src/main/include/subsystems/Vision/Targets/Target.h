#pragma once

#include "subsystems/Vision/Cameras/Camera.h"

#include <opencv2/opencv.hpp>

#include <atomic>
#include <string>

namespace Vision {

class Camera;

class Target {
 public:
  virtual void setup(Camera *camera) = 0;
  virtual void run(cv::Mat &frame) = 0;
  const std::string name = "";

  void resetOffset();
  std::pair<double, double> getOffset();

 protected:
  std::atomic<double> m_horizontalOffset;
  std::atomic<double> m_verticalOffset;
};

}