#pragma once

#include "subsystems/IndicatorLights/Effect.h"
#include "subsystems/IndicatorLights/Solid.h"

#include <memory>

namespace IndicatorLights {

class Wave : public Effect {
 public:
  Wave(std::shared_ptr<Effect> overlayedEffect, int speedMillis = 1000);
  void run() override;
  void reset() override;

 private:
  std::shared_ptr<Effect> m_overlayedEffect;
  double m_posPerFrame;
  double m_currentPos;
};

}