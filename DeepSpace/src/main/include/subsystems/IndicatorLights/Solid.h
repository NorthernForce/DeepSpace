#pragma once

#include "subsystems/IndicatorLights/Effect.h"

namespace IndicatorLights {

class Solid : public Effect {
 public:
  Solid(std::vector<uint8_t> color);
  std::vector<std::vector<uint8_t>> run() override;

 private:
  std::vector<uint8_t> m_color;
};

}