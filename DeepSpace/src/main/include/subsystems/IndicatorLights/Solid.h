#pragma once

#include "subsystems/IndicatorLights/Effect.h"

namespace IndicatorLights {

class Solid : public Effect {
 public:
  Solid(std::vector<uint8_t> color);
  void run() override;
  void reset() override;
};

}