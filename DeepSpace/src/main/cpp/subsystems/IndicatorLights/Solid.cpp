#include "subsystems/IndicatorLights/Solid.h"

IndicatorLights::Solid::Solid(std::vector<uint8_t> color) {
  m_color = color;
  m_colors.push_back(std::vector<uint8_t>{0, 0, 0});
}

void IndicatorLights::Solid::run() {
  m_colors[0] = m_color;

  m_done = true;
}

void IndicatorLights::Solid::reset() {
  m_done = false;
  m_colors[0] = std::vector<uint8_t>{0, 0, 0};
}