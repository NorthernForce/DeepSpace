/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ClimberDrive.h"

#include "RobotMap.h"
#include "commands/ClimberDriveSlowWhileLowered.h"

const double ClimberDrive::k_speedForward = 0.5;
const double ClimberDrive::k_speedBackward = -0.5;
const double ClimberDrive::k_speedIdle = 0.15;

const double ClimberDrive::k_stopDelay = 0.1;

ClimberDrive::ClimberDrive() : Subsystem("ExampleSubsystem") {
  m_masterTalonWheels.reset(new WPI_TalonSRX (RobotMap::ClimberDrive::k_driveMotor_id));

  m_masterTalonWheels->ConfigContinuousCurrentLimit(12, 800);
}

void ClimberDrive::InitDefaultCommand() {
  SetDefaultCommand(new ClimberDriveSlowWhileLowered());
}

void ClimberDrive::setSpeed(double speed) {
    m_masterTalonWheels->Set(speed);
}

void ClimberDrive::stop() {
    setSpeed(0.0);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
