/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "RobotMap.h"

OI::OI() {
  // Process operator interface input here.
  m_driverController.reset(new frc::XboxController(RobotMap::OI::k_driverController_id));
  m_manipulatorController.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController_id));

  // m_driverController->SetRumble(frc::GenericHID::kLeftRumble, 1.0);
}

