/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionFollowLimelight.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include "Robot.h"

const double VisionFollowLimelight::k_p = 1.3;
const double VisionFollowLimelight::k_i = 0.01;
const double VisionFollowLimelight::k_d = 0.1;

const double VisionFollowLimelight::k_maxTurnSpeed = 0.35;

// It seems to aim to the right
const double VisionFollowLimelight::k_targetOffset = 0.0;

VisionFollowLimelight::VisionFollowLimelight() : Command("VisionFollowLimelight") {
  Requires(Robot::m_vision.get());
  Requires(Robot::m_driveTrain.get());

  // Add smart dashboard stuff
  frc::SmartDashboard::PutNumber("FollowLimelight: P", k_p);
  frc::SmartDashboard::PutNumber("FollowLimelight: I", k_i);
  frc::SmartDashboard::PutNumber("FollowLimelight: D", k_d);
  
  frc::SmartDashboard::PutNumber("FollowLimelight: offset", k_targetOffset);
}

// Called just before this Command runs the first time
void VisionFollowLimelight::Initialize() {
  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}

// Called repeatedly when this Command is scheduled to run
void VisionFollowLimelight::Execute() {
  double p = frc::SmartDashboard::GetNumber("FollowLimelight: P", k_p);
  double i = frc::SmartDashboard::GetNumber("FollowLimelight: I", k_i);
  double d = frc::SmartDashboard::GetNumber("FollowLimelight: D", k_d);

  double tx = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);

  // PID Loop math taken from some site on the internet
  m_error = tx / 27 + frc::SmartDashboard::GetNumber("FollowLimelight: offset", k_targetOffset);
  if (m_error == 0) {
    m_integral = 0;
  }

  m_integral += m_error * Robot::kDefaultPeriod;
  m_derivative = (m_error - m_error_prior) / Robot::kDefaultPeriod;

  double rotation = p*m_error + i*m_integral + d*m_derivative;

  m_error_prior = m_error;

  // Limit max turn speed
  if (rotation < k_maxTurnSpeed * -1) {
    rotation = k_maxTurnSpeed * -1;
  }
  else if (rotation > k_maxTurnSpeed) {
    rotation = k_maxTurnSpeed;
  }

  auto steeringControls = Robot::m_oi->getSteeringControls();

  Robot::m_driveTrain->arcDrive(steeringControls.first, rotation + steeringControls.second * 0.6);
}

// Make this return true when this Command no longer needs to run execute()
bool VisionFollowLimelight::IsFinished() { return false; }

// Called once after isFinished returns true
void VisionFollowLimelight::End() {
  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionFollowLimelight::Interrupted() { End(); }