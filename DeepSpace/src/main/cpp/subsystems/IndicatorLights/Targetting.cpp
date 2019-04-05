#include "subsystems/IndicatorLights/Targetting.h"

#include "Robot.h"
#include "subsystems/IndicatorLightsManager.h"

const std::string IndicatorLights::Targetting::k_cameraName = "Targeter";

IndicatorLights::Targetting::Targetting() {
  m_colors = std::vector<std::vector<uint8_t>>(IndicatorLights::Manager::k_maxLEDs, std::vector<uint8_t>{0, 0, 0});
}

void IndicatorLights::Targetting::run() {
  // if (Robot::m_vision->getTarget(k_cameraName) == "") {
  //   return;
  // }

  double targetOffset = Robot::m_vision->getOffset(Robot::m_vision->getTarget(k_cameraName)).first;

  for (int ledI = 0; ledI < m_colors.size(); ledI++) {
    double ledOffset = ledI / (double)(m_colors.size() - 1) * 2 - 1;
    double distanceOffset = std::abs(ledOffset - targetOffset);

    if (distanceOffset >= 0.8) {
      m_colors[ledI] = std::vector<uint8_t>{0, 255, 0};
    }
    else if (distanceOffset >= 0.5) {
      m_colors[ledI] = std::vector<uint8_t>{0, 255, (uint8_t)std::round(255.0 * (0.8 - distanceOffset) / 0.3)};
    }
    else if (distanceOffset >= 0.2) {
      m_colors[ledI] = std::vector<uint8_t>{0, (uint8_t)std::round(255.0 * (distanceOffset - 0.2) / 0.3), 255};
    }
    else {
      m_colors[ledI] = std::vector<uint8_t>{0, 0, 255};
    }
  }
}

void IndicatorLights::Targetting::reset() {}