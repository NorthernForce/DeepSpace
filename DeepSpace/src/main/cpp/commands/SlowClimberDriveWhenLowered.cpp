/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SlowClimberDriveWhenLowered.h"

#include "Robot.h"

SlowClimberDriveWhenLowered::SlowClimberDriveWhenLowered() {
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void SlowClimberDriveWhenLowered::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SlowClimberDriveWhenLowered::Execute() {
  if (Robot::m_climber->AtUpperLimit()) {
    Robot::m_climber->DriveStop();
  }
  else {
    Robot::m_climber->DriveWheels(k_slowSpeed);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool SlowClimberDriveWhenLowered::IsFinished() { return false; }

// Called once after isFinished returns true
void SlowClimberDriveWhenLowered::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SlowClimberDriveWhenLowered::Interrupted() {}
