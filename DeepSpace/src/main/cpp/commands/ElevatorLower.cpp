/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorLower.h"
#include "Robot.h"

ElevatorLower::ElevatorLower() : Command("ElevatorLower") {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorLower::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorLower::Execute() {
  Robot::m_elevator->lower(); 
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorLower::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorLower::End() {
  Robot::m_elevator->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorLower::Interrupted() { End(); }
