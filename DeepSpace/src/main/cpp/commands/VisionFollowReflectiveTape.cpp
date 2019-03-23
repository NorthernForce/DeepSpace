/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionFollowReflectiveTape.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include "Robot.h"

const std::string VisionFollowReflectiveTape::k_cameraName = "Elevator";
const std::string VisionFollowReflectiveTape::k_targetName = "ReflectiveTape";

const double VisionFollowReflectiveTape::k_p = 0;
const double VisionFollowReflectiveTape::k_i = 0;
const double VisionFollowReflectiveTape::k_d = 0;

const double VisionFollowReflectiveTape::k_iterationTime = 0.02;

const double VisionFollowReflectiveTape::k_maxTurnSpeed = 0.7;

VisionFollowReflectiveTape::VisionFollowReflectiveTape() {
  Requires(Robot::m_vision.get());
  Requires(Robot::m_driveTrain.get());

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
  // Not really sure how this works...
  m_error = Robot::m_vision->getOffset(k_targetName).first;
  // std::cout << "error: " << m_error;
  m_integral += m_error * k_iterationTime;
  m_derivative = (m_error - m_error_prior) / k_iterationTime;
  // double output = k_p*m_error + k_i*m_integral + k_d*m_derivative;
  // For tuning:
  double output = frc::SmartDashboard::GetNumber("CameraTracking: P", k_p) * m_error 
                + frc::SmartDashboard::GetNumber("CameraTracking: I", k_i) * m_integral
                + frc::SmartDashboard::GetNumber("CameraTracking: D", k_d) * m_derivative;
  m_error_prior = m_error;

  if (output < k_maxTurnSpeed * -1) {
    output = k_maxTurnSpeed * -1;
  }
  else if (output > k_maxTurnSpeed) {
    output = k_maxTurnSpeed;
  }

  // std::cout << " output: " << output << "\n";

  auto steeringControls = Robot::m_oi->getSteeringControls();

  if (m_error != 0) {
    Robot::m_driveTrain->arcDrive(steeringControls.first, output);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool VisionFollowReflectiveTape::IsFinished() {
  // return (std::abs(m_error) < 0.1);
  return false;
}

// Called once after isFinished returns true
void VisionFollowReflectiveTape::End() {
  Robot::m_vision->setTarget("Elevator", "");
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionFollowReflectiveTape::Interrupted() { End(); }