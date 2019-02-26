/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorRetract.h"
#include "Robot.h"
#include "RobotMap.h"

ElevatorRetract::ElevatorRetract() {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorRetract::Initialize() {
  Robot::m_elevator->Retract();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRetract::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRetract::IsFinished() { return false; }

// Called once after isFinished returns true
void ElevatorRetract::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRetract::Interrupted() {}
