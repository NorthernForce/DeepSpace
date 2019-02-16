/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeCargo.h"

#include <iostream>

#include "Robot.h"

IntakeCargo::IntakeCargo() {
  Requires(Robot::m_cargoManipulator.get());
}

// Called just before this Command runs the first time
void IntakeCargo::Initialize() {
  std::cout << "IntakeCargo Started" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void IntakeCargo::Execute() {
  Robot::m_cargoManipulator->setSpeed(CargoManipulator::k_intakeSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeCargo::IsFinished() { return false; }

// Called once after isFinished returns true
void IntakeCargo::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeCargo::Interrupted() {}
