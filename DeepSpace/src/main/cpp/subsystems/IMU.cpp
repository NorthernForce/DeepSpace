/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IMU.h"

IMU::IMU() : Subsystem("ExampleSubsystem") {
  try { 
  m_ahrs.reset(new AHRS(SPI::Port::kMXP));
  }
  catch (std::exception ex ) {
    printf("Unable to initialize the gyro - you have the wheel");
  }
}

void IMU::InitDefaultCommand() {
  // Set the default command for a subsystem here.
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
