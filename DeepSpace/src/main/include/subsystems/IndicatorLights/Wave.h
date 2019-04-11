#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <memory>

namespace IndicatorLights {

class Wave : public Effect {
 public:
  Wave(int numberOfLeds, int speedMillis, std::shared_ptr<Effect> overlayedEffect);
  void run() override;
  void reset() override;

 private:
  std::shared_ptr<Effect> m_overlayedEffect;
  double m_posPerFrame;

  double m_currentPos;
};

}