#include "subsystems/IndicatorLights/Wave.h"

#include "subsystems/IndicatorLightsManager.h"

IndicatorLights::Wave::Wave(std::shared_ptr<Effect> overlayedEffect, int speedMillis) {
  m_colors = std::vector<std::vector<uint8_t>>(Manager::k_maxLEDs, std::vector<uint8_t>{0, 0, 0});
  m_posPerFrame = Manager::k_framePeriodMillis / (double)speedMillis;
  m_overlayedEffect = overlayedEffect;

  reset();
}

void IndicatorLights::Wave::run() {
  if (m_overlayedEffect->isDone()) {
      m_overlayedEffect->reset();
  }

  m_overlayedEffect->run();

  auto newColors = m_overlayedEffect->getColors();

  if (newColors.size() < m_colors.size()) {
      auto appendColors = std::vector<std::vector<uint8_t>>(m_colors.size() - newColors.size(), newColors.back());
      newColors.insert(newColors.end(), appendColors.begin(), appendColors.end());
  }

  for (int i = 0; i < m_colors.size(); i++) {
    double physicalPos = i / (double)(m_colors.size() - 1);
    double decreaser = 1 - std::abs(m_currentPos - physicalPos);
    decreaser = decreaser * 0.25 + 0.75;

    m_colors[i][0] = newColors[i][0] * decreaser;
    m_colors[i][1] = newColors[i][1] * decreaser;
    m_colors[i][2] = newColors[i][2] * decreaser;
  }

  m_currentPos += m_posPerFrame;

  if (m_currentPos > 1 || m_currentPos < 0) {
    m_currentPos *= -1;
    m_currentPos += 2 * m_posPerFrame;
  }
}

void IndicatorLights::Wave::reset() {
  m_colors = std::vector<std::vector<uint8_t>>(m_colors.size(), std::vector<uint8_t>{0, 0, 0});
  m_posPerFrame = std::abs(m_posPerFrame);
  m_currentPos = 0;

  m_done = false;
}