/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OpenClaw.h"
#include "Robot.h"
#include "RobotMap.h"

OpenClaw::OpenClaw() : frc::TimedCommand(RobotMap::Claw::k_timeToOpen) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void OpenClaw::Initialize() {
    Robot::m_claw->SetOpen();
}