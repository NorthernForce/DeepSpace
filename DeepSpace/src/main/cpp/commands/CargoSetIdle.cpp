/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoSetIdle.h"

#include "Robot.h"

CargoSetIdle::CargoSetIdle(bool idleValue) {
  Requires(Robot::m_cargoManipulator.get());

  m_idleValue = idleValue;
}

// Called just before this Command runs the first time
void CargoSetIdle::Initialize() {
  Robot::m_cargoManipulator->setIdle(m_idleValue);
}

// Called repeatedly when this Command is scheduled to run
void CargoSetIdle::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool CargoSetIdle::IsFinished() { return true; }

// Called once after isFinished returns true
void CargoSetIdle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoSetIdle::Interrupted() {}
