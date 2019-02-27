/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowReflectiveTape.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"

FollowReflectiveTape::FollowReflectiveTape() {
  Requires(Robot::m_vision.get());
  Requires(Robot::m_driveTrain.get());
}

// Called just before this Command runs the first time
void FollowReflectiveTape::Initialize() {
  Robot::m_vision->setTarget(k_cameraName, k_targetName);
}

// Called repeatedly when this Command is scheduled to run
void FollowReflectiveTape::Execute() {
  // Not really sure how this works...
  m_error = Robot::m_vision->getOffset(k_targetName).first * -1;
  m_integral += m_error * k_iterationTime;
  m_derivative = (m_error - m_error_prior) / k_iterationTime;
  double output = k_p*m_error + k_i*m_integral + k_d*m_derivative;
  m_error_prior = m_error;

  Robot::m_driveTrain->arcDrive(0, output);
}

// Make this return true when this Command no longer needs to run execute()
bool FollowReflectiveTape::IsFinished() {
  // return (std::abs(m_error) < 0.1);
  return false;
}

// Called once after isFinished returns true
void FollowReflectiveTape::End() {
  Robot::m_vision->setTarget("Elevator", "");
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowReflectiveTape::Interrupted() {
  Robot::m_vision->setTarget("Elevator", "");
  Robot::m_driveTrain->arcDrive(0, 0);
}