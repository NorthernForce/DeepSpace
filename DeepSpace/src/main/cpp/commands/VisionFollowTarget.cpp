/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionFollowTarget.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"

const double VisionFollowTarget::k_p = 1.3;
const double VisionFollowTarget::k_i = 0.01;
const double VisionFollowTarget::k_d = 0.1;

const double VisionFollowTarget::k_maxTurnSpeed = 0.35;

// It seems to aim to the right
const double VisionFollowTarget::k_targetOffset = 0;

VisionFollowTarget::VisionFollowTarget(std::string cameraName, std::string targetName) : Command("VisionFollowTarget") {
  Requires(Robot::m_vision.get());
  Requires(Robot::m_driveTrain.get());

  m_cameraName = cameraName;
  m_targetName = targetName;

  // Add smart dashboard stuff
  frc::SmartDashboard::PutNumber("CameraTracking: P", k_p);
  frc::SmartDashboard::PutNumber("CameraTracking: I", k_i);
  frc::SmartDashboard::PutNumber("CameraTracking: D", k_d);
}

// Called just before this Command runs the first time
void VisionFollowTarget::Initialize() {
  Robot::m_vision->setTarget(m_cameraName, m_targetName);
}

// Called repeatedly when this Command is scheduled to run
void VisionFollowTarget::Execute() {
  double p = frc::SmartDashboard::GetNumber("CameraTracking: P", k_p);
  double i = frc::SmartDashboard::GetNumber("CameraTracking: I", k_i);
  double d = frc::SmartDashboard::GetNumber("CameraTracking: D", k_d);

  // PID Loop math taken from some site on the internet
  m_error = Robot::m_vision->getOffset(m_targetName).first + k_targetOffset;
  if (m_error == 0) {
    m_integral = 0;
  }

  m_integral += m_error * Robot::kDefaultPeriod;
  m_derivative = (m_error - m_error_prior) / Robot::kDefaultPeriod;

  double rotation = k_p*m_error + k_i*m_integral + k_d*m_derivative;

  m_error_prior = m_error;

  // Limit max turn speed
  if (rotation < k_maxTurnSpeed * -1) {
    rotation = k_maxTurnSpeed * -1;
  }
  else if (rotation > k_maxTurnSpeed) {
    rotation = k_maxTurnSpeed;
  }

  auto steeringControls = Robot::m_oi->getSteeringControls();

  Robot::m_driveTrain->arcDrive(steeringControls.first, rotation + steeringControls.second * 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool VisionFollowTarget::IsFinished() { return false; }

// Called once after isFinished returns true
void VisionFollowTarget::End() {
  Robot::m_vision->enableTargetting(m_cameraName, false);
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionFollowTarget::Interrupted() { End(); }