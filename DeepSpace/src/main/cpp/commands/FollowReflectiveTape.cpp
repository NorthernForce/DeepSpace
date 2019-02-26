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

  std::shared_ptr<TargetPIDSource> m_pidSource;
  m_pidSource.reset(new TargetPIDSource());

  std::shared_ptr<DriveTrainPIDOutput> m_pidOutput;
  m_pidOutput.reset(new DriveTrainPIDOutput());
  // m_pidOutput = new DriveTrainPIDOutput();

  m_pidController.reset(new frc::PIDController(k_p, k_i, k_d, k_f, m_pidSource.get(), m_pidOutput.get()));

  frc::SmartDashboard::PutData("Reflective Tape Follower", m_pidController.get());
}

// Called just before this Command runs the first time
void FollowReflectiveTape::Initialize() {
  Robot::m_vision->setTarget("Elevator", "ReflectiveTape");

  m_pidController->SetEnabled(true);
}

// Called repeatedly when this Command is scheduled to run
void FollowReflectiveTape::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool FollowReflectiveTape::IsFinished() { return false; }

// Called once after isFinished returns true
void FollowReflectiveTape::End() {
  Robot::m_vision->setTarget("Elevator", "");

  m_pidController->SetEnabled(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowReflectiveTape::Interrupted() {
  Robot::m_vision->setTarget("Elevator", "");

  m_pidController->SetEnabled(false);
}

double FollowReflectiveTape::TargetPIDSource::PIDGet() {
  return Robot::m_vision->getOffset("ReflectiveTape").first;
}

void FollowReflectiveTape::DriveTrainPIDOutput::PIDWrite(double output) {
  Robot::m_driveTrain->arcDrive(0, output);
}