/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbEvenlyUp.h"

#include "Robot.h"
  
const double ClimbEvenlyUp::k_maxFrontTilt = -2;
const double ClimbEvenlyUp::k_maxBackTilt = -0.5;
const double ClimbEvenlyUp::k_targetTilt = (k_maxBackTilt + k_maxFrontTilt) / 2;
const double ClimbEvenlyUp::k_rangeOfTilt = (k_maxBackTilt - k_maxFrontTilt) / 2;

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
  double val = (angle - k_targetTilt) / k_rangeOfTilt;

  if (val > 1) {
    Robot::m_elevator->setSpeed(0);
    Robot::m_climber->setSpeed(-1);
  }
  else if (val > 0) {
    Robot::m_elevator->setSpeed(1 - val);
    Robot::m_climber->setSpeed(-1);
  }
  else if (val < -1) {
    Robot::m_elevator->setSpeed(-1);
    Robot::m_climber->setSpeed(0);
  }
  else if (val < 0) {
    Robot::m_elevator->setSpeed(-1);
    Robot::m_climber->setSpeed(-1 - val);
  }
  else {
    Robot::m_elevator->setSpeed(-1);
    Robot::m_climber->setSpeed(-1);
  }

  // if (angle <= k_maxFrontTilt) {
  //   Robot::m_elevator->lower();
  //   Robot::m_climber->stop();
  // }
  // else if (angle >= k_maxBackTilt) {
  //   Robot::m_elevator->stop();
  //   Robot::m_climber->lower();
  // }
  // else {
  //   Robot::m_elevator->lower();
  //   Robot::m_climber->lower();
  // }
}

// Make this return true when this Command no longer needs to run execute()
bool ClimbEvenlyUp::IsFinished() {
  return Robot::m_climber->atUpperLimit();
}

// Called once after isFinished returns true
void ClimbEvenlyUp::End() {
  Robot::m_elevator->stop();
  Robot::m_climber->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbEvenlyUp::Interrupted() { End(); }
