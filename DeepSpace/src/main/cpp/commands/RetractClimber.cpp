/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractClimber.h"

#include "Robot.h"

RetractClimber::RetractClimber() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
   Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void RetractClimber::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RetractClimber::Execute() {
  Robot::m_climber->Raise();
}

// Make this return true when this Command no longer needs to run execute()
bool RetractClimber::IsFinished() { 
  return Robot::m_climber->AtUpperLimit();
 }

// Called once after isFinished returns true
void RetractClimber::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractClimber::Interrupted() {}
