/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbEvenlyUp.h"

#include "Robot.h"

ClimbEvenlyUp::ClimbEvenlyUp() {
  Requires(Robot::m_elevator.get());
  Requires(Robot::m_climber.get());
  Requires(Robot::m_imu.get());
}

// Called just before this Command runs the first time
void ClimbEvenlyUp::Initialize() {
  if (!m_climbingStarted) {
    m_climbingStarted = true;
    Robot::m_imu->resetAngle();
  }
}

// Called repeatedly when this Command is scheduled to run
void ClimbEvenlyUp::Execute() {
  auto angle = Robot::m_imu->getAngle();

  // So, stopping it should work, but it may be jerky.
  // I just think it happens to be safer.
  if (angle <= stopBackThreshold) {
    Robot::m_elevator->Lower();
    Robot::m_climber->Stop();
  }
  else if (angle >= stopFrontThreshold) {
    Robot::m_elevator->Stop();
    Robot::m_climber->Lower();
  }
  else {
    Robot::m_elevator->Lower();
    Robot::m_climber->Lower();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbEvenlyUp::IsFinished() {
  return Robot::m_climber->AtUpperLimit();
}

// Called once after isFinished returns true
void ClimbEvenlyUp::End() {
  Robot::m_elevator->Stop();
  Robot::m_climber->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbEvenlyUp::Interrupted() { End(); }
