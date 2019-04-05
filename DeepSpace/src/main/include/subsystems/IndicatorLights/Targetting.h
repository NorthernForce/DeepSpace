#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <string>

namespace IndicatorLights {

class Targetting : public Effect {
 public:
  Targetting();
  void run() override;

 private:
  const static std::string k_cameraName;
};

}