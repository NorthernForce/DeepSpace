/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoManipulator.h"

#include "RobotMap.h"

CargoManipulator::CargoManipulator() : Subsystem("CargoManipulator") {
  m_motor.reset(new WPI_TalonSRX(RobotMap::CargoManipulator::k_motor_id));
}

void CargoManipulator::InitDefaultCommand() {}

// Speed is a value from -1.0 to 1.0
void CargoManipulator::setSpeed(double speed) {
  m_motor->Set(speed);
}