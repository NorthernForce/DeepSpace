/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/GenericHID.h>
#include <frc/buttons/Trigger.h>

class ComboButton : public frc::Trigger {
 public:
  ComboButton(std::shared_ptr<frc::GenericHID> joystick, int buttonNumberPrimary, int buttonNumberSecondary);
  bool Get() override;

 private:
  std::shared_ptr<frc::GenericHID> m_joystick;
  int m_primaryBtn;
  int m_secondaryBtn;
};
