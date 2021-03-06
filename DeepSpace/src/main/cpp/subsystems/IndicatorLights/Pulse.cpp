#include "subsystems/IndicatorLights/Pulse.h"

#include <cmath>

IndicatorLights::Pulse::Pulse(std::vector<uint8_t> color, double speed) {
  m_color = color;
  
  if (speed > 1 || speed < 0) {
      speed = 0.05;
  }
  m_speed = speed;

  reset();
}

void IndicatorLights::Pulse::run() {
  // if (m_done) {
  //   return;
  // }

  std::vector<uint8_t> color;

  if (m_sum >= 1) {
    m_speed *= -1;

    color = m_color;
  }
  else if (m_sum <= 0) {
    m_done = true;

    color = std::vector<uint8_t>{0, 0, 0};
  }
  else {
    color = std::vector<uint8_t>{(uint8_t)(m_color[0] * m_sum), (uint8_t)(m_color[1] * m_sum), (uint8_t)(m_color[2] * m_sum)};
  }

  m_colors[0] = color;
  
  m_sum += m_speed;
}

void IndicatorLights::Pulse::reset() {
  m_sum = 0;
  m_speed = std::abs(m_speed);
  m_done = false;

  m_colors = std::vector<std::vector<uint8_t>>{std::vector<uint8_t>{0, 0, 0}};
  
  run();
}