/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimberStop.h"

#include "Robot.h"

ClimberStop::ClimberStop() {
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void ClimberStop::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberStop::Execute() {
    Robot::m_climber->Stop();
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberStop::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimberStop::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberStop::Interrupted() {}
