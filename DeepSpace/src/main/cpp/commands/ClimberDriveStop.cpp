/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberDriveStop.h"

#include "Robot.h"

ClimberDriveStop::ClimberDriveStop() : TimedCommand("ClimberDriveStop", ClimberDrive::k_stopDelay) {
  Requires(Robot::m_climberDrive.get());
}

// Called just before this Command runs the first time
void ClimberDriveStop::Initialize() {
  Robot::m_climberDrive->stop();
}