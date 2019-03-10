/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Claw.h"
  
const bool Claw::k_clawOpenValue = 1;
const bool Claw::k_clawClosedValue = 0;
const bool Claw::k_clawRaisedValue = 0;
const bool Claw::k_clawLoweredValue = 1;

const double Claw::k_timeToOpen = 0.4;
const double Claw::k_timeToClose = 0.4;
const double Claw::k_timeToRaise = 0.4;
const double Claw::k_timeToLower = 0.4;

Claw::Claw() : Subsystem("Claw") {
  m_clawSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_pcm_id, RobotMap::Claw::k_clawSolenoid_id));
  m_raiseSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_pcm_id, RobotMap::Claw::k_raiseSolenoid_id));
}

void Claw::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Claw::open() {
  m_clawSolenoid->Set(k_clawOpenValue);

}

void Claw::close() {
  m_clawSolenoid->Set(k_clawClosedValue);

}

void Claw::raise() {
  m_raiseSolenoid->Set(k_clawRaisedValue);
  m_raisedState = State::Raised;
}

void Claw::lower() {
  m_raiseSolenoid->Set(k_clawLoweredValue);
  m_raisedState = State::Lowered;
}

bool Claw::isRaised() {
  return m_raisedState == State::Raised;

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
