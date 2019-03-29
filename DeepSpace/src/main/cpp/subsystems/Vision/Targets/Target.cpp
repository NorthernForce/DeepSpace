#include "subsystems/Vision/Targets/Target.h"

void Vision::Target::resetOffset() {
  m_horizontalOffset = 0;
  m_verticalOffset = 0;
}

std::pair<double, double> Vision::Target::getOffset() {
  return std::make_pair(m_horizontalOffset.load(), m_verticalOffset.load());
}