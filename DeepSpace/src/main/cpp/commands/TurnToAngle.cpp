/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToAngle.h"

#include "Robot.h"

const double TurnToAngle::k_p = 1.3;
const double TurnToAngle::k_i = 0;
const double TurnToAngle::k_d = 0;

const double TurnToAngle::k_maxTurnSpeed = 0.35;
const double TurnToAngle::k_minError = 0.05;

TurnToAngle::TurnToAngle(double targetAngle) {
  Requires(Robot::m_imu.get());
  Requires(Robot::m_driveTrain.get());

  m_targetAngle = targetAngle;

  // Add smart dashboard stuff
  frc::SmartDashboard::PutNumber("TurnToAngle: P", k_p);
  frc::SmartDashboard::PutNumber("TurnToAngle: I", k_i);
  frc::SmartDashboard::PutNumber("TurnToAngle: D", k_d);
}

// Called just before this Command runs the first time
void TurnToAngle::Initialize() {
  m_totalTargetAngle = Robot::m_imu->getRotation() + m_targetAngle;
  m_integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToAngle::Execute() {
  double p = frc::SmartDashboard::GetNumber("TurnToAngle: P", k_p);
  double i = frc::SmartDashboard::GetNumber("TurnToAngle: I", k_i);
  double d = frc::SmartDashboard::GetNumber("TurnToAngle: D", k_d);

  // PID Loop math taken from some site on the internet
  m_error = (Robot::m_imu->getRotation() - m_totalTargetAngle) / 180;
  if (m_error == 0) {
    m_integral = 0;
  }

  std::cout << "error: " << m_error;

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

  std::cout << " rotation: " << rotation << " goal: " << m_totalTargetAngle << " angle: " << Robot::m_imu->getRotation() << std::endl;

  auto steeringControls = Robot::m_oi->getSteeringControls();

  Robot::m_driveTrain->arcDrive(steeringControls.first, rotation + steeringControls.second * 0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToAngle::IsFinished() {
  return (std::abs(m_error) < k_minError);
}

// Called once after isFinished returns true
void TurnToAngle::End() {
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToAngle::Interrupted() { End(); }
