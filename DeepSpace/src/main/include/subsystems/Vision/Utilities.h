#pragma once

#include <opencv2/opencv.hpp>

namespace Vision {
  class Utilities {
   public:
    static cv::Point CalcAvgPoint(cv::Point a, cv::Point b);
    static double CalcLineLength(cv::Point a, cv::Point b);
    static double CalcLineAngle(cv::Point origin, cv::Point outer);
    static double CalcLineAngleDeg(cv::Point origin, cv::Point outer);
    const static double k_Pi;
    const static double k_HalfPi;
    const static double k_QuaterPi;
    const static double k_DegToRad;
    const static double k_RadToDeg;
  };
}