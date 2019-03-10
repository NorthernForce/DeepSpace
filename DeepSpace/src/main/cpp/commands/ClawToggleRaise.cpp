/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClawToggleRaise.h"

#include "Robot.h"

ClawToggleRaise::ClawToggleRaise() : TimedCommand(k_duration) {
  Requires(Robot::m_claw.get());
}

// Called just before this Command runs the first time
void ClawToggleRaise::Initialize() {
  if (Robot::m_claw->isRaised()) {
    Robot::m_claw->lower();
  }
  else {
    Robot::m_claw->raise();
  }
}
