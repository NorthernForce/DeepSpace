/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleClawRaise.h"
#include "Robot.h"

ToggleClawRaise::ToggleClawRaise(): TimedCommand(RobotMap::Claw::k_timeToRaise) {
  Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void ToggleClawRaise::Initialize() {
  if(Robot::m_claw->IfRaised()){
    Robot::m_claw->ClawLower();
  } else {
    Robot::m_claw->ClawRaise();
  }
}
