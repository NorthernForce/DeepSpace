/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/XboxController.h>
#include <frc/Joystick.h>

class OI {
 public:
  OI();

  std::pair<double, double> getSteeringControls();

 private:
  std::shared_ptr<frc::XboxController> m_driverController;
  std::shared_ptr<frc::Joystick> m_manipulatorController1;
  std::shared_ptr<frc::Joystick> m_manipulatorController2;
  std::shared_ptr<frc::XboxController> m_manipulatorController3;
};
