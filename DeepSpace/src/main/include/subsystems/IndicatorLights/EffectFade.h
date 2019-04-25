#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <memory>

namespace IndicatorLights {

class EffectFade : public Effect {
 public:
  EffectFade(std::shared_ptr<Effect> oldEffect, std::shared_ptr<Effect> newEffect, int speedMillis = 300);
  void run() override;
  void reset() override;

  std::shared_ptr<Effect> m_oldEffect;
  std::shared_ptr<Effect> m_newEffect;

 private:
  double m_posPerFrame;
  double m_currentPos;

  std::vector<std::vector<uint8_t>> m_newColors;
  std::vector<std::vector<uint8_t>> m_oldColors;
  std::vector<std::vector<uint8_t>> m_colorsDiff;
};

}