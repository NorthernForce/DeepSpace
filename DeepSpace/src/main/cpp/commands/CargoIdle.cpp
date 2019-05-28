/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoIdle.h"

#include "Robot.h"

CargoIdle::CargoIdle() {
  Requires(Robot::m_cargoManipulator.get());
}

// Called just before this Command runs the first time
void CargoIdle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CargoIdle::Execute() {
  if (Robot::m_cargoManipulator->getIdle()) {
    Robot::m_cargoManipulator->setSpeed(CargoManipulator::k_idleSpeed);
  }
  else {
    Robot::m_cargoManipulator->setSpeed(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CargoIdle::IsFinished() { return false; }

// Called once after isFinished returns true
void CargoIdle::End() {
  Robot::m_cargoManipulator->setSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoIdle::Interrupted() { End(); }
