#include "subsystems/Vision/Utilities.h"

cv::Point Vision::Utilities::CalcAvgPoint(cv::Point a, cv::Point b) {
  return cv::Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

std::tuple<cv::Point, cv::Point, cv::Point, cv::Point> Vision::Utilities::FindExtremePoints(std::vector<cv::Point> contour) {
  cv::Rect rect = cv::boundingRect(contour);
  cv::Point startPoint = cv::Point(rect.x, rect.y);
  cv::Point endPoint = cv::Point(rect.x + rect.width, rect.y + rect.height);

  cv::Point topLeft = contour[0], topRight = contour[0],
            rightTop = contour[0], rightBot = contour[0],
            botLeft = contour[0], botRight = contour[0],
            leftTop = contour[0], leftBot = contour[0];
  
  for (auto &point : contour) {
    if (point.y == startPoint.y) {
      if (point.x < topLeft.x) {
        topLeft = point;
      }
      if (point.x > topRight.x) {
        topRight = point;
      }
    }
    else if (point.y == endPoint.y) {
      if (point.x < botLeft.x) {
        botLeft = point;
      }
      if (point.x > botRight.x) {
        botRight = point;
      }
    }

    if (point.x == startPoint.x) {
      if (point.y < leftTop.y) {
        leftTop = point;
      }
      if (point.y > leftBot.y) {
        leftBot = point;
      }
    }
    else if (point.x == endPoint.x) {
      if (point.y < rightTop.y) {
        rightTop = point;
      }
      if (point.y > rightBot.y) {
        rightBot = point;
      }
    }
  }
  
  return std::make_tuple(
    CalcAvgPoint(topLeft, topRight),
    CalcAvgPoint(rightTop, rightBot),
    CalcAvgPoint(botLeft, botRight),
    CalcAvgPoint(leftTop, leftBot)
  );
}