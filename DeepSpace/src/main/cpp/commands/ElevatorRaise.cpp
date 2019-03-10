/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorRaise.h"

#include "Robot.h"

ElevatorRaise::ElevatorRaise() {
	Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorRaise::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorRaise::Execute() {
  Robot::m_elevator->Raise(); 
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRaise::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorRaise::End() {
  Robot::m_elevator->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRaise::Interrupted() { End(); }
