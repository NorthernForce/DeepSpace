/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoEject.h"

#include "Robot.h"

CargoEject::CargoEject() : Command("CargoEject") {
  Requires(Robot::m_cargoManipulator.get());
}

// Called just before this Command runs the first time
void CargoEject::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CargoEject::Execute() {
  Robot::m_cargoManipulator->setSpeed(CargoManipulator::k_ejectSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool CargoEject::IsFinished() { return false; }

// Called once after isFinished returns true
void CargoEject::End() {
  Robot::m_cargoManipulator->setSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoEject::Interrupted() { End(); }
