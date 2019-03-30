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
  ComboButton(frc::Trigger *button1, frc::Trigger *button2);
  bool Get() override;

 private:
  frc::Trigger *m_button1;
  frc::Trigger *m_button2;
};
