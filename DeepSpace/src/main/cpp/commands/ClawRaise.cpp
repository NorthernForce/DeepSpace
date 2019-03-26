/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawRaise.h"

#include "Robot.h"

ClawRaise::ClawRaise(): TimedCommand("ClawRaise", Claw::k_timeToRaise) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void ClawRaise::Initialize() {
    Robot::m_claw->raise();
}
