#include "subsystems/IndicatorLights/Targetting.h"

#include "Robot.h"
#include "subsystems/IndicatorLightsManager.h"

#include <iostream>

const std::string IndicatorLights::Targetting::k_cameraName = "Targeter";

const double IndicatorLights::Targetting::k_redThreshold = 0.7;
const double IndicatorLights::Targetting::k_greenThreshold = 0.05;
const double IndicatorLights::Targetting::k_averageThreshold = (k_redThreshold + k_greenThreshold) / 2;
const double IndicatorLights::Targetting::k_rangeThreshold = (k_redThreshold - k_greenThreshold) / 2;

IndicatorLights::Targetting::Targetting() {
  m_colors.resize(Manager::k_maxLEDs);

  reset();
}

void IndicatorLights::Targetting::run() {
  double targetOffset = Robot::m_vision->getOffset(Robot::m_vision->getTarget(k_cameraName)).first;

  for (int ledI = 0; ledI < m_colors.size(); ledI++) {
    double ledOffset = ledI / (double)(m_colors.size() - 1) * 2 - 1;
    double distanceOffset = std::abs(ledOffset - targetOffset);

    if (distanceOffset >= k_redThreshold) {
      m_colors[ledI] = std::vector<uint8_t>{0, 255, 0};
    }
    else if (distanceOffset >= k_averageThreshold) {
      m_colors[ledI] = std::vector<uint8_t>{0, 255, (uint8_t)std::round(255.0 * (k_redThreshold - distanceOffset) / k_rangeThreshold)};
    }
    else if (distanceOffset >= k_greenThreshold) {
      m_colors[ledI] = std::vector<uint8_t>{0, (uint8_t)std::round(255.0 * (distanceOffset - k_greenThreshold) / k_rangeThreshold), 255};
    }
    else {
      m_colors[ledI] = std::vector<uint8_t>{0, 0, 255};
    }
  }
}

void IndicatorLights::Targetting::reset() {
  m_colors = std::vector<std::vector<uint8_t>>(m_colors.size(), std::vector<uint8_t>{0, 255, 0});
}