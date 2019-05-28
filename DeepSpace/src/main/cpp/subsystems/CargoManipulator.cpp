/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoManipulator.h"

#include "RobotMap.h"

#include "commands/CargoIdle.h"

const double CargoManipulator::k_ejectSpeed = -1.0;
const double CargoManipulator::k_intakeSpeed = 0.6;

// Duration in micro seconds
const int CargoManipulator::k_divideSpeedDuration = 200 * 1000;
const double CargoManipulator::k_divideSpeedAmount = 0.5;

const double CargoManipulator::k_rampRate = 0.2;
const double CargoManipulator::k_secondaryCurrentLimit = 16.0;
const int CargoManipulator::k_currentLimit = 10;

const double CargoManipulator::k_idleSpeed = 0.1;

CargoManipulator::CargoManipulator() : Subsystem("CargoManipulator") {
  m_motor.reset(new rev::CANSparkMax(RobotMap::CargoManipulator::k_motor_id, rev::CANSparkMax::MotorType::kBrushed));

  // m_divideSpeedTimer.reset(new frc::Timer());
  m_motor->SetSecondaryCurrentLimit(k_secondaryCurrentLimit);
  m_motor->SetSmartCurrentLimit(k_currentLimit);
  m_motor->SetOpenLoopRampRate(k_rampRate);
}

void CargoManipulator::InitDefaultCommand() {
  SetDefaultCommand(new CargoIdle());
}

void CargoManipulator::Periodic() {
  // if (GetCurrentCommandName().empty()) {
  //   m_divideSpeedTimerReset = true;
  // }
}

// Speed is a value from -1.0 to 1.0
void CargoManipulator::setSpeed(double speed) {
  // if (m_divideSpeedTimerReset) {
  //     m_divideSpeedTimer->Reset();
  //     m_divideSpeedTimer->Start();

  //     m_divideSpeedTimerReset = false;
  // }

  // if (m_divideSpeedTimer->Get() < k_divideSpeedDuration) {
    m_motor->Set(speed);
  // }
  // else {
  //   m_motor->Set(speed * k_divideSpeedAmount);
  // }
}

void CargoManipulator::setIdle(bool idle) {
  m_idle = idle;
}

bool CargoManipulator::getIdle() {
  return m_idle;
}