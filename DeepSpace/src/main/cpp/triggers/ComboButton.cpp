/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "triggers/ComboButton.h"

ComboButton::ComboButton(frc::Trigger *button1, frc::Trigger *button2)
  : m_button1(button1), m_button2(button2) {}

bool ComboButton::Get() {
  return (m_button1->Get() && m_button2->Get());
}
