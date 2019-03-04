/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ComputerVisionTargetTape.h"

#include "Robot.h"

ComputerVisionTargetTape::ComputerVisionTargetTape() {
  Requires(Robot::m_vision.get());
}

// Called just before this Command runs the first time
void ComputerVisionTargetTape::Initialize() {
  std::cout << "Target set" << std::endl;
  Robot::m_vision->setTarget("Elevator", "ReflectiveTape");
}

// Called repeatedly when this Command is scheduled to run
void ComputerVisionTargetTape::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ComputerVisionTargetTape::IsFinished() { return true; }

// Called once after isFinished returns true
void ComputerVisionTargetTape::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ComputerVisionTargetTape::Interrupted() {}
