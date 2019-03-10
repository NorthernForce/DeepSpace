/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionTargetReflectiveTape.h"

#include "Robot.h"

VisionTargetReflectiveTape::VisionTargetReflectiveTape() {
  Requires(Robot::m_vision.get());
}

// Called just before this Command runs the first time
void VisionTargetReflectiveTape::Initialize() {
  Robot::m_vision->setTarget("Elevator", "ReflectiveTape");
}

// Called repeatedly when this Command is scheduled to run
void VisionTargetReflectiveTape::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool VisionTargetReflectiveTape::IsFinished() { return true; }

// Called once after isFinished returns true
void VisionTargetReflectiveTape::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionTargetReflectiveTape::Interrupted() {}
