#include "subsystems/IndicatorLights/Solid.h"

IndicatorLights::Solid::Solid(std::vector<uint8_t> color) {
  m_color = color;
}

std::vector<std::vector<uint8_t>> IndicatorLights::Solid::run() {
  m_done = true;
  
  return std::vector<std::vector<uint8_t>>{m_color};
}