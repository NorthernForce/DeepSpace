/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberDriveSlowWhileLowered.h"

#include "Robot.h"

ClimberDriveSlowWhileLowered::ClimberDriveSlowWhileLowered() : Command("ClimberDriveSlowWhileLowered") {
  Requires(Robot::m_climberDrive.get());
}

// Called just before this Command runs the first time
void ClimberDriveSlowWhileLowered::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberDriveSlowWhileLowered::Execute() {
  if (Robot::m_climber->atUpperLimit()) {
    Robot::m_climberDrive->stop();
  }
  else {
    Robot::m_climberDrive->setSpeed(ClimberDrive::k_speedIdle);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDriveSlowWhileLowered::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberDriveSlowWhileLowered::End() {
  Robot::m_climberDrive->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDriveSlowWhileLowered::Interrupted() { End(); }
