/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawOpen.h"

#include "Robot.h"

ClawOpen::ClawOpen() : frc::TimedCommand("ClawOpen", Claw::k_timeToOpen) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void ClawOpen::Initialize() {
    Robot::m_claw->open();
}

