/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawClose.h"

#include "Robot.h"

ClawClose::ClawClose() : frc::TimedCommand(k_duration) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void ClawClose::Initialize() {
    Robot::m_claw->SetClosed();
}
