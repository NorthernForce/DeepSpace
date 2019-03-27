/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/GenericHID.h>
#include <frc/buttons/Trigger.h>

class SimpleAxis : public frc::Trigger {
 public:
  SimpleAxis(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, double threshold = 0.5);
  bool Get() override;

 private:
  std::shared_ptr<frc::GenericHID> m_joystick;
  int m_axisNumber;
  double m_threshold;
};
