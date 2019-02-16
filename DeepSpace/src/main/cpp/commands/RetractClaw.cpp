/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RetractClaw.h"
#include "Robot.h"
#include "RobotMap.h"

RetractClaw::RetractClaw() : TimedCommand(RobotMap::Claw::k_timeToRetract) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void RetractClaw::Initialize() {
  Robot::m_claw->ClawRetract();
}

