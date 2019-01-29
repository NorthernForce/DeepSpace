/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>

OI::OI() {
  // Process operator interface input here.
  driverController.reset(new frc::Joystick(k_xbox_controller_id));
  driverController->SetRumble(frc::GenericHID::kLeftRumble, 1.0);

  // frc::Joystick *exampleStick;
  // exampleStick = new frc::Joystick(0);
}
