/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionTargetReflectiveTape.h"

#include "Robot.h"

VisionTargetReflectiveTape::VisionTargetReflectiveTape() : TimedCommand(Vision::Target::k_targetChangeDelay) {
  Requires(Robot::m_vision.get());
}

// Called just before this Command runs the first time
void VisionTargetReflectiveTape::Initialize() {
  Robot::m_vision->setTarget("Elevator", "ReflectiveTape");
}