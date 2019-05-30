/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IMU.h"

#include "Robot.h"

const double IMU::k_rumbleMultiplier = 1;

const double IMU::k_maxJerkForCollision = 0.2;
const double IMU::k_collisionPeriod = 0.25; // Seconds

IMU::IMU() : Subsystem("ExampleSubsystem") {
  try { 
    m_ahrs.reset(new AHRS(SPI::Port::kMXP));
  }
  catch (std::exception ex) {
    // This could be a problem
    printf("Unable to initialize the gyro - you have the wheel");
  }

  m_collisionTimer.reset(new frc::Timer());
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

  double currJerk = std::sqrt(std::pow(currJerkX, 2) + std::pow(currJerkY, 2));

  if (currJerk >= k_maxJerkForCollision) {
    m_collisionTimer->Reset();
    m_collisionTimer->Start();

    std::cout << "A collision has been detected --- ";
  }

  std::cout << "Jerk: " << currJerk << "\n";

  Robot::m_oi->setControllerRumble(currJerk * currJerk * k_rumbleMultiplier);
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

bool IMU::hasCollided() {
  if (m_collisionTimer->Get() < k_collisionPeriod) {
    return true;
  }
  else {
    m_collisionTimer->Stop();
    return false;
  }
}