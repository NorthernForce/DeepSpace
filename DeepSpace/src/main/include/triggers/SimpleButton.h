/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/buttons/Trigger.h>
#include <frc/GenericHID.h>

class SimpleButton : public frc::Trigger {
 public:
  SimpleButton(std::shared_ptr<frc::GenericHID> joystick, int btnNumber);
  bool Get() override;

 private:
  std::shared_ptr<frc::GenericHID> m_joystick;
  int m_btnNumber;
};
