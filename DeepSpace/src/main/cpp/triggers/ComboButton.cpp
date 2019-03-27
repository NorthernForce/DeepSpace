/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/ComboButton.h"

ComboButton::ComboButton(std::shared_ptr<frc::GenericHID> joystick, int buttonNumberPrimary, int buttonNumberSecondary)
  : m_joystick(joystick), m_primaryBtn(buttonNumberPrimary), m_secondaryBtn(buttonNumberSecondary) {}

bool ComboButton::Get() {
  return (m_joystick->GetRawButton(m_primaryBtn) && m_joystick->GetRawButton(m_secondaryBtn));
}
