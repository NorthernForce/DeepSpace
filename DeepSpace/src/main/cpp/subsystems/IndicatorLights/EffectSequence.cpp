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

  if (m_effects[m_effectIndex]->isDone()) {
    m_effectIndex++;

    if (m_effectIndex >= m_effects.size()) {
      m_done = true;
    }
    else if (m_effects[m_effectIndex]->isDone()) {
      m_effects[m_effectIndex]->reset();
    }
  }
}

void IndicatorLights::EffectSequence::reset() {
  m_effectIndex = 0;

  m_effects[m_effectIndex]->reset();

  m_done = false;
}