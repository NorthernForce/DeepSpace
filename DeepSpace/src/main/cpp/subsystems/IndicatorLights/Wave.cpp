#include "subsystems/IndicatorLights/Wave.h"

#include "subsystems/IndicatorLightsManager.h"

#include <iostream>

IndicatorLights::Wave::Wave(std::shared_ptr<Effect> overlayedEffect, int speedMillis, double depth, double spread) {
  m_colors.resize(Manager::k_maxLEDs);
  m_posPerFrame = Manager::k_framePeriodMillis / (double)speedMillis;
  m_overlayedEffect = overlayedEffect;
  m_depth = depth;
  m_spread = spread;

  reset();
}

void IndicatorLights::Wave::run() {
  if (m_overlayedEffect->isDone()) {
    m_done = true;
    return;
  }

  m_overlayedEffect->run();

  auto newColors = m_overlayedEffect->getColors();

  if (newColors.size() < m_colors.size()) {
      auto appendColors = std::vector<std::vector<uint8_t>>(m_colors.size() - newColors.size(), newColors.back());
      newColors.insert(newColors.end(), appendColors.begin(), appendColors.end());
  }

  for (int i = 0; i < m_colors.size(); i++) {
    double physicalPos = i / (double)(m_colors.size() - 1);
    double decreaser = (1 - std::abs(m_currentPos - physicalPos) - m_spread) / m_spread;
    if (decreaser > 0) {
      decreaser = decreaser * m_depth + (1 - m_depth);
    }
    else {
      decreaser = 1 - m_depth;
    }

    m_colors[i][0] = newColors[i][0] * decreaser;
    m_colors[i][1] = newColors[i][1] * decreaser;
    m_colors[i][2] = newColors[i][2] * decreaser;

    // std::cout << " " << decreaser;
  }
  // std::cout << "\n";

  m_currentPos += m_posPerFrame;

  if (m_currentPos > 1 || m_currentPos < 0) {
    m_posPerFrame *= -1;
    // m_currentPos += 2 * m_posPerFrame;
  }
}

void IndicatorLights::Wave::reset() {
  m_colors.assign(m_colors.size(), std::vector<uint8_t>{0, 0, 0});
  m_posPerFrame = std::abs(m_posPerFrame);
  m_currentPos = 0;

  m_overlayedEffect->reset();

  m_done = false;
}