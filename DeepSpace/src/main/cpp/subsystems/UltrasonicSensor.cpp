/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor() : Subsystem("UltrasonicSensor") {
  m_ultrasonicSensor.reset(new frc::Ultrasonic(RobotMap::UltrasonicSensor::k_ultrasonicPing_id, RobotMap::UltrasonicSensor::k_ultrasonicEcho_id));

}

void UltrasonicSensor::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

double UltrasonicSensor::GetDistanceToWall() {
  return m_ultrasonicSensor->GetRangeInches();

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
