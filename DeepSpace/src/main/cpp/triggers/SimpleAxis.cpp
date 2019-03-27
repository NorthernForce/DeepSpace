/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/SimpleAxis.h"

SimpleAxis::SimpleAxis(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, double threshold) 
  : m_joystick(joystick), m_axisNumber(axisNumber), m_threshold(threshold) {}

bool SimpleAxis::Get() { 
  return (m_joystick->GetRawAxis(m_axisNumber) > m_threshold);
}
