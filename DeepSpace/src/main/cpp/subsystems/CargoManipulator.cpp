/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoManipulator.h"

#include "RobotMap.h"

CargoManipulator::CargoManipulator() : Subsystem("CargoManipulator") {
  m_motor.reset(new rev::CANSparkMax(RobotMap::CargoManipulator::k_motor_id, rev::CANSparkMax::MotorType::kBrushed));

  m_motor->SetSmartCurrentLimit(k_currentLimit);

  m_divideSpeedTimer.reset(new frc::Timer());
}

void CargoManipulator::InitDefaultCommand() {}

void CargoManipulator::Periodic() {
  if (GetCurrentCommandName().empty()) {
    m_divideSpeedTimerReset = true;
  }
}

// Speed is a value from -1.0 to 1.0
void CargoManipulator::setSpeed(double speed) {
  if (m_divideSpeedTimerReset) {
      m_divideSpeedTimer->Reset();
      m_divideSpeedTimer->Start();

      m_divideSpeedTimerReset = false;
  }

  if (m_divideSpeedTimer->Get() < k_divideSpeedDuration) {
    m_motor->Set(speed);
  }
  else {
    m_motor->Set(speed * k_divideSpeedAmount);
  }
}