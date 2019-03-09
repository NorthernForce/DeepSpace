/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LowerClaw.h"
#include "Robot.h"
#include "RobotMap.h"

LowerClaw::LowerClaw() : TimedCommand(Claw::k_timeToLower) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void LowerClaw::Initialize() {
  Robot::m_claw->ClawLower();
}

