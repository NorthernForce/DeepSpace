#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <string>

namespace IndicatorLights {

class Targetting : public Effect {
 public:
  Targetting();
  void run() override;
  void reset() override;

 private:
  const static std::string k_cameraName;

  const static double k_redThreshold;
  const static double k_greenThreshold;
  const static double k_averageThreshold;
  const static double k_rangeThreshold;
};

}