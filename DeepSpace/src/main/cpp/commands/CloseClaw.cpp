/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CloseClaw.h"
#include "Robot.h"
#include "RobotMap.h"

CloseClaw::CloseClaw() : frc::TimedCommand(Claw::k_timeToClose) {
    Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void CloseClaw::Initialize() {
    Robot::m_claw->SetClosed();
}
