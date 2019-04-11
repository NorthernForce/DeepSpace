#pragma once

#include "subsystems/IndicatorLights/Effect.h"

#include <string>

namespace IndicatorLights {

class Morse : public Effect {
 public:
  Morse(std::string message = "", int speedOfDot = 8, std::vector<uint8_t> onColor = std::vector<uint8_t>{0, 255, 0}, std::vector<uint8_t> offColor = std::vector<uint8_t>{0, 0, 0});
  void run() override;
  void reset() override;

 private:
  std::string m_message;
  int m_speedOfDot;
  std::vector<uint8_t> m_onColor;
  std::vector<uint8_t> m_offColor;

  int m_counter = 0;
  int m_stringIndex = 0;
  int m_codeIndex = 0;
  std::string m_code = "";
};

}