/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RaiseClaw.h"
#include "Robot.h"
#include "RobotMap.h"

RaiseClaw::RaiseClaw(): TimedCommand(Claw::k_timeToRaise) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void RaiseClaw::Initialize() {
    Robot::m_claw->ClawRaise();
}
