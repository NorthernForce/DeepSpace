/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/EvenlyClimbDown.h"

#include "Robot.h"

EvenlyClimbDown::EvenlyClimbDown() {
  Requires(Robot::m_elevator.get());
  Requires(Robot::m_climber.get());
  Requires(Robot::m_imu.get());
}

// Called just before this Command runs the first time
void EvenlyClimbDown::Initialize() {
  // Not sure if we wanna zero the imu.
}

// Called repeatedly when this Command is scheduled to run
void EvenlyClimbDown::Execute() {
  auto angle = Robot::m_imu->getAngle();

  // So, stopping it should work, but it may be jerky.
  // I just think it happens to be safer.
  if (angle <= stopBackThreshold) {
    Robot::m_elevator->Stop();
    Robot::m_climber->Lower();
  }
  else if (angle >= stopFrontThreshold) {
    Robot::m_elevator->Lower();
    Robot::m_climber->Stop();
  }
  else {
    Robot::m_elevator->Lower();
    Robot::m_climber->Lower();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool EvenlyClimbDown::IsFinished() {
  return Robot::m_climber->AtLowerLimit();
}

// Called once after isFinished returns true
void EvenlyClimbDown::End() {
  Robot::m_elevator->Stop();
  Robot::m_climber->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EvenlyClimbDown::Interrupted() { End(); }
