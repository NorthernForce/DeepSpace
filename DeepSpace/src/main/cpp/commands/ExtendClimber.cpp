/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendClimber.h"

#include "Robot.h"

ExtendClimber::ExtendClimber() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void ExtendClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ExtendClimber::Execute() {
  Robot::m_climber->Lower();
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendClimber::IsFinished() { 
  return Robot::m_climber->AtLowerLimit();
 }

// Called once after isFinished returns true
void ExtendClimber::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendClimber::Interrupted() {}
