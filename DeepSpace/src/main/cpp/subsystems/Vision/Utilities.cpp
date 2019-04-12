#include "subsystems/Vision/Utilities.h"

cv::Point Vision::Utilities::CalcAvgPoint(cv::Point a, cv::Point b) {
  return cv::Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

double Vision::Utilities::CalcLineLength(cv::Point a, cv::Point b) {
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

double Vision::Utilities::CalcLineAngle(cv::Point origin, cv::Point outer) {
  double angle = std::atan2(origin.y - outer.y, outer.x - origin.x);

  if (angle < 0) {
    angle += 6.28318530718;
  }

  return angle;
}

double Vision::Utilities::CalcLineAngleDeg(cv::Point origin, cv::Point outer) {
  return CalcLineAngle(origin, outer) * 57.2957795131;
}