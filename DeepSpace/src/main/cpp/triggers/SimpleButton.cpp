/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/SimpleButton.h"

SimpleButton::SimpleButton(std::shared_ptr<frc::GenericHID> joystick, int btnNumber)
  : m_joystick(joystick), m_btnNumber(btnNumber) {}

bool SimpleButton::Get() {
  return m_joystick->GetRawButton(m_btnNumber);
}
