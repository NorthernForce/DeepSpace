/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ComputerVisionTargetNothing.h"

#include "Robot.h"

ComputerVisionTargetNothing::ComputerVisionTargetNothing() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ComputerVisionTargetNothing::Initialize() {
  std::cout << "Target destroyed" << std::endl;
  Robot::m_vision->setTarget("Elevator");
  // Robot::m_vision->setTarget("ReflectiveTape");
}

// Called repeatedly when this Command is scheduled to run
void ComputerVisionTargetNothing::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ComputerVisionTargetNothing::IsFinished() { return true; }

// Called once after isFinished returns true
void ComputerVisionTargetNothing::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ComputerVisionTargetNothing::Interrupted() {}
