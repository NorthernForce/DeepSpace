#include "subsystems/IndicatorLights/Turning.h"

#include "Robot.h"

IndicatorLights::Turning::Turning() {
  m_colors.push_back(std::vector<uint8_t>{0, 0, 0});
}

void IndicatorLights::Turning::run() {
  double h = (Robot::m_imu->getRotation() + 180) / 360.0;
  double s = 1;
  double v = 1;

  // Courtesy of https://stackoverflow.com/questions/8208905/hsv-0-255-to-rgb-0-255?rq=1
  double r, g, b;

  int i = h * 6;
  double f = h * 6 - i;
  double p = v * (1 - s);
  double q = v * (1 - f * s);
  double t = v * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: r = v, g = t, b = p; break;
    case 1: r = q, g = v, b = p; break;
    case 2: r = p, g = v, b = t; break;
    case 3: r = p, g = q, b = v; break;
    case 4: r = t, g = p, b = v; break;
    case 5: r = v, g = p, b = q; break;
  }

  m_colors[0][0] = b * 255;
  m_colors[0][1] = g * 255;
  m_colors[0][2] = r * 255;
}