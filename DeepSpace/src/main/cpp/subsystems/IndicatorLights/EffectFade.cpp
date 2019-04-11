#include "subsystems/IndicatorLights/EffectFade.h"

#include "subsystems/IndicatorLightsManager.h"

IndicatorLights::EffectFade::EffectFade(std::shared_ptr<Effect> oldEffect, std::shared_ptr<Effect> newEffect, int speedMillis) {
  m_oldEffect = oldEffect;
  m_newEffect = newEffect;

  m_colors = std::vector<std::vector<uint8_t>>(1, std::vector<uint8_t>{0, 0, 0});

  m_posPerFrame = Manager::k_framePeriodMillis / (double)speedMillis;

  reset();
}

void IndicatorLights::EffectFade::run() {
  if (m_hasRunNew) {
    m_newEffect->run();
    m_hasRunNew = true;
  }

  auto m_newColors = m_newEffect->getColors();
  auto m_oldColors = m_oldEffect->getColors();

  for (int i = 0; i < m_colors.size(); i++) {
  }

  m_currentPos += m_posPerFrame;

  if (m_currentPos > 1) {
    m_done = true;
  }
}

void IndicatorLights::EffectFade::reset() {
  m_colors = std::vector<std::vector<uint8_t>>(1, std::vector<uint8_t>{0, 0, 0});

  m_hasRunNew = false;

//   m_posPerFrame = std::abs(m_posPerFrame);
  m_currentPos = 0;

  m_done = false;
}