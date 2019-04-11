#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <memory>

namespace IndicatorLights {

class EffectFade : public Effect {
 public:
  EffectFade(std::shared_ptr<Effect> oldEffect, std::shared_ptr<Effect> newEffect, int speedMillis = 500);
  void run() override;
  void reset() override;

  std::shared_ptr<Effect> m_oldEffect;
  std::shared_ptr<Effect> m_newEffect;

 private:
  bool m_hasRunNew = false;

  double m_posPerFrame;
  double m_currentPos;
};

}