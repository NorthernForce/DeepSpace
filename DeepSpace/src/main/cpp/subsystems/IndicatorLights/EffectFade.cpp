#include "subsystems/IndicatorLights/EffectFade.h"

#include "subsystems/IndicatorLightsManager.h"

#include <iostream>

IndicatorLights::EffectFade::EffectFade(std::shared_ptr<Effect> oldEffect, std::shared_ptr<Effect> newEffect, int speedMillis) {
  m_oldEffect = oldEffect;
  m_newEffect = newEffect;

  m_posPerFrame = Manager::k_framePeriodMillis / (double)speedMillis;

  reset();
}

void IndicatorLights::EffectFade::run() {
  if (m_done) {
    return;
  }

  for (int i = 0; i < m_colors.size(); i++) {
    m_colors[i][0] = m_oldColors[i][0] - m_colorsDiff[i][0] * m_currentPos;
    m_colors[i][1] = m_oldColors[i][1] - m_colorsDiff[i][1] * m_currentPos;
    m_colors[i][2] = m_oldColors[i][2] - m_colorsDiff[i][2] * m_currentPos;
  }

  m_currentPos += m_posPerFrame;

  if (m_currentPos > 1) {
    m_done = true;
  }
}

void IndicatorLights::EffectFade::reset() {
  m_newColors = m_newEffect->getColors();
  m_oldColors = m_oldEffect->getColors();

  int size = (m_newColors.size() > m_oldColors.size()) ? m_newColors.size() : m_oldColors.size();

  m_newColors.resize(size, m_newColors.back());
  m_oldColors.resize(size, m_oldColors.back());

  m_colorsDiff = std::vector<std::vector<int>>(size, std::vector<int>{0, 0, 0});
  for (int x = 0; x < size; x++) {
    m_colorsDiff[x][0] = m_oldColors[x][0] - m_newColors[x][0];
    m_colorsDiff[x][1] = m_oldColors[x][1] - m_newColors[x][1];
    m_colorsDiff[x][2] = m_oldColors[x][2] - m_newColors[x][2];
  }

  m_currentPos = 0;

  m_colors = m_oldColors;

  m_done = false;
}