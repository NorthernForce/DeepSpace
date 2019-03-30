/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/SimpleAxis.h"

SimpleAxis::SimpleAxis(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, double lowerThreshold, double upperThreshold) 
  : m_joystick(joystick), m_axisNumber(axisNumber), m_lowerThreshold(lowerThreshold), m_upperThreshold(upperThreshold) {}

bool SimpleAxis::Get() {
  double value = m_joystick->GetRawAxis(m_axisNumber);

  if (value < m_lowerThreshold || value > m_upperThreshold) {
    return false;
  }
  else {
    return true;
  }
}
