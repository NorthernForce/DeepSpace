#include "subsystems/IndicatorLights/EffectSequence.h"

#include <iostream>

IndicatorLights::EffectSequence::EffectSequence(std::vector<std::shared_ptr<Effect>> effects) {
  m_effects = effects;

  reset();
}

void IndicatorLights::EffectSequence::run() {
  if (m_done) {
      return;
  }

  m_effects[m_effectIndex]->run();
  m_colors = m_effects[m_effectIndex]->getColors();

  std::cout << "run" << std::endl;

  if (m_effects[m_effectIndex]->isDone()) {
    m_effectIndex++;

    std::cout << "switching" << std::endl;

    if (m_effectIndex >= m_effects.size()) {
      m_done = true;
    }
    else {
      m_effects[m_effectIndex]->reset();
    }
  }
}

void IndicatorLights::EffectSequence::reset() {
  m_effectIndex = 0;

  std::cout << "reset" << std::endl;

  m_effects[m_effectIndex]->reset();

  m_done = false;
}