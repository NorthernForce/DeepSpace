/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberDriveForward.h"

#include "Robot.h"

ClimberDriveForward::ClimberDriveForward() {
  Requires(Robot::m_climberDrive.get());
}

// Called just before this Command runs the first time
void ClimberDriveForward::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberDriveForward::Execute() {
Robot::m_climberDrive->setSpeed(k_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDriveForward::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberDriveForward::End() {
 Robot::m_climberDrive->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDriveForward::Interrupted() { End(); }
