/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionFollowReflectiveTape.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"

const std::string VisionFollowReflectiveTape::k_cameraName = "Targeter";
const std::string VisionFollowReflectiveTape::k_targetName = "ReflectiveTape";

const double VisionFollowReflectiveTape::k_p = 1.5;
const double VisionFollowReflectiveTape::k_i = 0.05;
const double VisionFollowReflectiveTape::k_d = 0.1;

const double VisionFollowReflectiveTape::k_maxTurnSpeed = 0.35;

VisionFollowReflectiveTape::VisionFollowReflectiveTape() : Command("VisionFollowReflectiveTape") {
  Requires(Robot::m_vision.get());
  Requires(Robot::m_driveTrain.get());

  // Add smart dashboard stuff
  frc::SmartDashboard::PutNumber("CameraTracking: P", k_p);
  frc::SmartDashboard::PutNumber("CameraTracking: I", k_i);
  frc::SmartDashboard::PutNumber("CameraTracking: D", k_d);
}

// Called just before this Command runs the first time
void VisionFollowReflectiveTape::Initialize() {
  Robot::m_vision->setTarget(k_cameraName, k_targetName);
}

// Called repeatedly when this Command is scheduled to run
void VisionFollowReflectiveTape::Execute() {
  double p = frc::SmartDashboard::GetNumber("CameraTracking: P", k_p);
  double i = frc::SmartDashboard::GetNumber("CameraTracking: I", k_i);
  double d = frc::SmartDashboard::GetNumber("CameraTracking: D", k_d);

  // PID Loop math taken from some site on the internet
  m_error = Robot::m_vision->getOffset(k_targetName).first - 0.05;
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

  // std::cout << "VisionFollowReflectiveTape: rotation: " << rotation << "\n";

  Robot::m_driveTrain->arcDrive(Robot::m_oi->getSteeringControls().first, rotation);
}

// Make this return true when this Command no longer needs to run execute()
bool VisionFollowReflectiveTape::IsFinished() { return false; }

// Called once after isFinished returns true
void VisionFollowReflectiveTape::End() {
  Robot::m_vision->enableCamera(k_cameraName, false);
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionFollowReflectiveTape::Interrupted() { End(); }