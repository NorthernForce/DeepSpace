/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberDriveBackward.h"

#include "Robot.h"

ClimberDriveBackward::ClimberDriveBackward() {
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void ClimberDriveBackward::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberDriveBackward::Execute() {
  Robot::m_climber->driveBackward();
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDriveBackward::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberDriveBackward::End() {
  Robot::m_climber->driveStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDriveBackward::Interrupted() { End(); }
