#pragma once

#include <opencv2/opencv.hpp>

namespace Vision {
  class Utilities {
   public:
    static cv::Point CalcAvgPoint(cv::Point a, cv::Point b);

    static std::tuple<cv::Point, cv::Point, cv::Point, cv::Point> FindExtremePoints(std::vector<cv::Point> contour);
  };
}