#include "subsystems/IndicatorLights/Solid.h"

IndicatorLights::Solid::Solid(std::vector<uint8_t> color) {
  m_colors = std::vector<std::vector<uint8_t>>{color};

  reset();
}

void IndicatorLights::Solid::run() {
  m_done = true;
}

void IndicatorLights::Solid::reset() {
  m_done = false;
}