#pragma once

#include <stdint.h>
#include <vector>

namespace IndicatorLights {

class Effect {
 public:
  virtual std::vector<std::vector<uint8_t>> run() = 0;
  bool isDone();
  
 protected:
  bool m_done = false;
};

}