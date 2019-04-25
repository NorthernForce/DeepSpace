#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <memory>

namespace IndicatorLights {

class EffectSequence : public Effect {
 public:
  EffectSequence(std::vector<std::shared_ptr<Effect>> effects);
  void run() override;
  void reset() override;

 private:
  std::vector<std::shared_ptr<Effect>> m_effects;
  int m_effectIndex;
};

}