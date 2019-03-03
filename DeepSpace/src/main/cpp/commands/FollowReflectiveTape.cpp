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

  frc::SmartDashboard::PutNumber("CameraTracking: P", k_p);
  frc::SmartDashboard::PutNumber("CameraTracking: I", k_i);
  frc::SmartDashboard::PutNumber("CameraTracking: D", k_d);
}

// Called just before this Command runs the first time
void FollowReflectiveTape::Initialize() {
  std::cout << "1" << std::endl;

  Robot::m_vision->setTarget(k_cameraName, k_targetName);
  std::cout << "2" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void FollowReflectiveTape::Execute() {
  std::cout << "3" << std::endl;
  // Not really sure how this works...
  m_error = Robot::m_vision->getOffset(k_targetName).first * -1;
  m_integral += m_error * k_iterationTime;
  m_derivative = (m_error - m_error_prior) / k_iterationTime;
  // double output = k_p*m_error + k_i*m_integral + k_d*m_derivative;
  // For tuning
  std::cout << "4" << std::endl;
  double output = frc::SmartDashboard::GetNumber("CameraTracking: P", k_p) * m_error 
                + frc::SmartDashboard::GetNumber("CameraTracking: I", k_i) * m_integral
                + frc::SmartDashboard::GetNumber("CameraTracking: D", k_d) * m_derivative;
  m_error_prior = m_error;
  std::cout << "4" << std::endl;

  Robot::m_driveTrain->arcDrive(0, output);
  std::cout << "5" << std::endl;
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