/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionTargetNothing.h"

#include "Robot.h"

VisionTargetNothing::VisionTargetNothing() : TimedCommand(k_duration) {
  Requires(Robot::m_vision.get());
}

// Called just before this Command runs the first time
void VisionTargetNothing::Initialize() {
  Robot::m_vision->setTarget("Elevator");
  // Robot::m_vision->setTarget("ReflectiveTape");
}