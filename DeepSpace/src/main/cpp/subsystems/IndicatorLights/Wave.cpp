#include "subsystems/IndicatorLights/Wave.h"

#include "subsystems/IndicatorLightsManager.h"

IndicatorLights::Wave::Wave(int numberOfLeds, int speedMillis, std::shared_ptr<Effect> overlayedEffect) {
  m_colors = std::vector<std::vector<uint8_t>>(numberOfLeds, std::vector<uint8_t>{0, 0, 0});
  m_posPerFrame = speedMillis / (double)Manager::k_framePeriodMillis;
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

//   for (int i = 0; i < m_colors.size(); i++) {
//     double decreaser = i / m_colors.size() - m_currentPos;

//     m_colors[i] = newColors[i];
//   }

//   m_currentPos += m_posPerFrame;

//   if (m_currentPos) {
    
//   }
}

void IndicatorLights::Wave::reset() {
  m_colors = std::vector<std::vector<uint8_t>>(m_colors.size(), std::vector<uint8_t>{0, 0, 0});
  m_currentPos = 0;
}