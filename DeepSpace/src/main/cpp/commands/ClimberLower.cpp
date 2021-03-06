/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberLower.h"

#include "Robot.h"

ClimberLower::ClimberLower() : Command("ClimberLower") {
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void ClimberLower::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberLower::Execute() {
    Robot::m_climber->lower();
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberLower::IsFinished() {
  return Robot::m_climber->atLowerLimit();
}

// Called once after isFinished returns true
void ClimberLower::End() {
  Robot::m_climber->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberLower::Interrupted() { End(); }
