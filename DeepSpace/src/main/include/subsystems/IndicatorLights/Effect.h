#pragma once

#include <stdint.h>
#include <vector>

namespace IndicatorLights {

class Effect {
 public:
  virtual void run() = 0;
  std::vector<std::vector<uint8_t>> getColors() {
    return m_colors;
  }
  bool isDone() {
    return m_done;
  }

 protected:
  bool m_done = false;
  std::vector<std::vector<uint8_t>> m_colors;
};

}