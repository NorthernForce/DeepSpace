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

  std::cout << "targetOffset: " << targetOffset << "\n";

  for (int ledI = 0; ledI < m_colors.size(); ledI++) {
    double ledOffset = ledI / (m_colors.size() - 1) * 2 - 1;
    double distanceOffset = std::abs(ledOffset - targetOffset);

    std::cout << "     ledOffset: " << ledOffset << " distanceOffset: " << distanceOffset << "\n";

    if (distanceOffset >= 1) {
      m_colors[ledI] = std::vector<uint8_t>{0, 0, 255};
    }
    else if (distanceOffset >= 0.5) {
      m_colors[ledI] = std::vector<uint8_t>{0, 255, (uint8_t)(255 * (0.5 - distanceOffset) / 0.5)};
    }
    else if (distanceOffset >= 0) {
      m_colors[ledI] = std::vector<uint8_t>{0, (uint8_t)(255 * (distanceOffset) / 0.5), 255};
    }
  }
}