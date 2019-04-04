#pragma once

#include "subsystems/IndicatorLights/Effect.h"

namespace IndicatorLights {

class Pulse : public Effect {
 public:
  Pulse(std::vector<uint8_t> color, double speed);
  void run() override;

 private:
  std::vector<uint8_t> m_color;
  double m_speed;
  double m_sum;
};

}