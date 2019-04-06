/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IMU.h"

#include "Robot.h"

// const double IMU::k_rumbleTimeout = 0.35;

// // To test
// const double IMU::k_maxJerk = 0.5;

const double IMU::k_rumbleMultiplier = 0.25;

IMU::IMU() : Subsystem("ExampleSubsystem") {
  try { 
    m_ahrs.reset(new AHRS(SPI::Port::kMXP));
  }
  catch (std::exception ex) {
    // This could be a problem
    printf("Unable to initialize the gyro - you have the wheel");
  }

  // m_rumbleTimer.reset(new frc::Timer());
}

void IMU::InitDefaultCommand() {
  // Set the default command for a subsystem here.
}

void IMU::Periodic() {
  // Collision Detection
  double currAccelX = m_ahrs->GetWorldLinearAccelX();
  double currJerkX = std::abs(currAccelX - m_lastAccelX);
  m_lastAccelX = currAccelX;

  double currAccelY = m_ahrs->GetWorldLinearAccelY();
  double currJerkY = std::abs(currAccelY - m_lastAccelY);
  m_lastAccelY = currAccelY;

  // std::cout << "currJerkX: " << currJerkX << " currJerkY: " << currJerkY << "\n";

  double rumble = (currJerkX > currJerkY) ? currJerkX : currJerkY;

  Robot::m_oi->setControllerRumble(rumble * k_rumbleMultiplier);

  // if (std::abs(currJerkX) > k_maxJerk || std::abs(currJerkY) > k_maxJerk) {
  //   Robot::m_oi->setControllerRumble(1);
  //   m_rumbleTimer->Reset();
  // }

  // if (m_rumbleTimer->Get() > k_rumbleTimeout) {
  //   Robot::m_oi->setControllerRumble(0);
  // }
}

float IMU::getAngle() {
  return m_ahrs->GetRoll() - m_angleOffset;
}

void IMU::resetAngle() {
  m_angleOffset = getAngle();
}

float IMU::getRotation() {
  return m_ahrs->GetYaw() - m_rotationOffset;
}

void IMU::resetRotation() {
  m_rotationOffset = getRotation();
}
