#pragma once

#include "subsystems/IndicatorLights/Effect.h"

namespace IndicatorLights {

class Turning : public Effect {
 public:
  Turning();
  void run() override;
};

}