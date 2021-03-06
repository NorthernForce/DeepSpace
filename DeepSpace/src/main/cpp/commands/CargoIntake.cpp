/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CargoIntake.h"

#include "Robot.h"

CargoIntake::CargoIntake() : Command("CargoIntake") {
  Requires(Robot::m_cargoManipulator.get());
}

// Called just before this Command runs the first time
void CargoIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CargoIntake::Execute() {
  Robot::m_cargoManipulator->setSpeed(CargoManipulator::k_intakeSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool CargoIntake::IsFinished() { return false; }

// Called once after isFinished returns true
void CargoIntake::End() {
  Robot::m_cargoManipulator->setSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CargoIntake::Interrupted() { End(); }
