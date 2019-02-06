/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Claw.h"

Claw::Claw() : Subsystem("Claw") {
  m_clawSolenoid.reset(new frc::Solenoid(RobotMap::Claw::k_clawSolenoid));


}

void Claw::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());

}

void Claw::SetOpen() {
  m_clawSolenoid->Set(RobotMap::Claw::k_clawOpenValue);

}

void Claw::SetClosed() {
  m_clawSolenoid->Set(RobotMap::Claw::k_clawClosedValue);

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
