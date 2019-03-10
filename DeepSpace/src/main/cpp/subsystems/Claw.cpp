/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Claw.h"

Claw::Claw() : Subsystem("Claw") {
  m_clawSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_pcm_id, RobotMap::Claw::k_clawSolenoid_id));
  m_raiseSolenoid.reset(new frc::Solenoid(RobotMap::PCM::k_pcm_id, RobotMap::Claw::k_raiseSolenoid_id));
}

void Claw::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Claw::SetOpen() {
  m_clawSolenoid->Set(k_clawOpenValue);

}

void Claw::SetClosed() {
  m_clawSolenoid->Set(k_clawClosedValue);

}

void Claw::ClawRaise() {
  m_raiseSolenoid->Set(k_clawRaisedValue);
  m_raisedState = State::Raised;
}

void Claw::ClawLower() {
  m_raiseSolenoid->Set(k_clawLoweredValue);
  m_raisedState = State::Lowered;
}

bool Claw::IfRaised() {
  return m_raisedState == State::Raised;

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
