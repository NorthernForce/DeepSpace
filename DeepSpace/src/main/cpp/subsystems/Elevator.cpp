/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

#include <ctre/Phoenix.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "RobotMap.h"
#include <iostream>
  
const int Elevator::timeoutMs = 10;
const int Elevator::noTimeoutMs = 0;
const double Elevator::freeSpeedRPM = 18730;
const double Elevator::maxSpeedRPM = freeSpeedRPM * 0.80;
const double Elevator::sensorUnitsPerRev = 256 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 12 counts per revolution
const double Elevator::maxSensorUnitsPer100ms = 1500; // sensorUnitsPerRev * maxSpeedRPM / 60 / 10;
const double Elevator::feedForwardGain = 0.5; // 1023 / maxSensorUnitsPer100ms;
const double Elevator::pGainPower = 0.15;
const double Elevator::pGainError = 100;
const double Elevator::pGain = 0.7; // (1023 * pGainPower) / pGainError;
const double Elevator::iGain = 0.007;
const double Elevator::iLimit = 1500;
const double Elevator::dGain = 0.07; //pGain / 10;
const double Elevator::timeToMaxSpeed = 0.75;
const int Elevator::slotIdx = 0;
const int Elevator::pidIdx = 0;
const int Elevator::defaultPeakAmps = 15;
const int Elevator::defaultContinuousCurrent = 12;
const double Elevator::rampTime = 0.5;

const double Elevator::k_elevatorMaxRaiseSpeed = 1;
const double Elevator::k_elevatorMaxLowerSpeed = 1; // abs of

const double Elevator::k_deployDelay = 0.8;
const double Elevator::k_motorStopDelay = 0.1;

Elevator::Elevator() : Subsystem("Elevator") { 
  m_primaryTalonElevator.reset(new WPI_TalonSRX (RobotMap::Elevator::k_primary_id));
  m_followerTalonElevator1.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower1_id));
  m_followerTalonElevator2.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower2_id));
  m_followerTalonElevator3.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower3_id));
  m_elevatorExtenderSolenoid.reset(new frc::Solenoid (RobotMap::PCM::k_pcm_id, RobotMap::Elevator::k_extenderSolenoid_id));
  m_elevatorRetracterSolenoid.reset(new frc::Solenoid (RobotMap::PCM::k_pcm_id, RobotMap::Elevator::k_retracterSolenoid_id));

  m_followerTalonElevator1->Follow(*m_primaryTalonElevator);
  m_followerTalonElevator2->Follow(*m_primaryTalonElevator);
  m_followerTalonElevator3->Follow(*m_primaryTalonElevator);

  disableForwardLimitSwitch();
  disableReverseLimitSwitch();

  //m_primaryTalonElevator->SetSensorPhase(true);
  m_primaryTalonElevator->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, pidIdx, 10);


  /* Set relevant frame periods to be at least as fast as periodic rate */
  m_primaryTalonElevator->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
  m_primaryTalonElevator->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

  /* Set the peak and nominal outputs */
  m_primaryTalonElevator->ConfigNominalOutputForward(0, 10);
  m_primaryTalonElevator->ConfigNominalOutputReverse(0, 10);
  m_primaryTalonElevator->ConfigPeakOutputForward(0.8, 10);
  m_primaryTalonElevator->ConfigPeakOutputReverse(-0.75, 10);

  /* Set Motion Magic gains in slot0 - see documentation */
  m_primaryTalonElevator->SelectProfileSlot(0, pidIdx);
  m_primaryTalonElevator->Config_kF(pidIdx, 0.0, 10);
  m_primaryTalonElevator->Config_kP(pidIdx, pGain, 10);
  m_primaryTalonElevator->Config_kI(pidIdx, iGain, 10);
  m_primaryTalonElevator->Config_kD(pidIdx, 0.0, 10);
  m_primaryTalonElevator->ConfigMaxIntegralAccumulator(pidIdx, iLimit, timeoutMs);
  m_primaryTalonElevator->ConfigOpenloopRamp(0.5);
  m_primaryTalonElevator->ConfigClosedloopRamp(0.3);

  /* Set acceleration and vcruise velocity - see documentation */
  m_primaryTalonElevator->ConfigMotionCruiseVelocity(3500, 10);
  m_primaryTalonElevator->ConfigMotionAcceleration(3000, 10);

  /* Zero the sensor */
  m_primaryTalonElevator->SetSelectedSensorPosition(0, pidIdx, 10);
/*
     //ConfigureCurrentLimits(defaultPeakAmps, defaultContinuousCurrent, timeoutMs);
	m_primaryTalonElevator->ConfigNominalOutputForward(+0.0, timeoutMs);
	m_primaryTalonElevator->ConfigNominalOutputReverse(-0.0, timeoutMs);
	m_primaryTalonElevator->SelectProfileSlot(slotIdx, pidIdx);
	//TODO: change these for more power 
	m_primaryTalonElevator->Config_kF(slotIdx, feedForwardGain, timeoutMs);
	m_primaryTalonElevator->Config_kP(slotIdx, pGain, timeoutMs);
	m_primaryTalonElevator->Config_kI(slotIdx, iGain, timeoutMs);
	m_primaryTalonElevator->ConfigMaxIntegralAccumulator(slotIdx, iLimit, timeoutMs);
	m_primaryTalonElevator->Config_kD(slotIdx, dGain, timeoutMs);
	m_primaryTalonElevator->ConfigMotionCruiseVelocity(maxSensorUnitsPer100ms, timeoutMs);
	m_primaryTalonElevator->ConfigMotionAcceleration(1500, timeoutMs); //(maxSensorUnitsPer100ms / timeToMaxSpeed, timeoutMs);
	m_primaryTalonElevator->ConfigSelectedFeedbackSensor(QuadEncoder, pidIdx, timeoutMs);

  SetHomePosition();
  */

  setHomePosition();
  setPosition(0);

  frc::SmartDashboard::PutNumber("Elevator: Raise Speed", k_elevatorMaxRaiseSpeed);
  frc::SmartDashboard::PutNumber("Elevator: Lower Speed", k_elevatorMaxLowerSpeed);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Elevator::Periodic() {
  if (this->atLowerLimit()) {
    this->setHomePosition();
  }
}

void Elevator::setSpeed(double speed) {
  if (speed > 1) {
    // m_primaryTalonElevator->Set(k_elevatorMaxRaiseSpeed);
    m_primaryTalonElevator->Set(frc::SmartDashboard::GetNumber("Elevator: Raise Speed", k_elevatorMaxRaiseSpeed));
  }
  else if (speed > 0) {
    // m_primaryTalonElevator->Set(speed * k_elevatorMaxRaiseSpeed);
    m_primaryTalonElevator->Set(speed * frc::SmartDashboard::GetNumber("Elevator: Raise Speed", k_elevatorMaxRaiseSpeed));
  }
  else if (speed < -1) {
    // m_primaryTalonElevator->Set(-1 * k_elevatorMaxLowerSpeed);
    m_primaryTalonElevator->Set(-1 * frc::SmartDashboard::GetNumber("Elevator: Lower Speed", k_elevatorMaxLowerSpeed));
  }
  else if (speed < 0) {
    // m_primaryTalonElevator->Set(speed * k_elevatorMaxLowerSpeed);
    m_primaryTalonElevator->Set(speed * frc::SmartDashboard::GetNumber("Elevator: Lower Speed", k_elevatorMaxLowerSpeed));
  }
  else {
    m_primaryTalonElevator->Set(0);
  }
}
void Elevator::raise(){
  setSpeed(1);
}
void Elevator::lower(){
  setSpeed(-1);
}
void Elevator::stop() {
  setSpeed(0);
}

void Elevator::setPosition(int setpoint)
{
  
  // std::cout << "Elevator set position to " << setpoint << std::endl;
	m_setpoint = setpoint;
  // std::cout << "Elevator set position to " << setpoint << " with magic" << std::endl;
	m_primaryTalonElevator->Set(ControlMode::Position, m_setpoint);
}

void Elevator::startClimb() {
  m_primaryTalonElevator->ConfigPeakOutputForward(1, 10);
  m_primaryTalonElevator->ConfigMotionAcceleration(2250);
  m_primaryTalonElevator->ConfigClosedloopRamp(0.5);
}

bool Elevator::atSetpoint()
{
  int pos = m_primaryTalonElevator->GetSelectedSensorPosition(pidIdx);
  int err = m_primaryTalonElevator->GetClosedLoopError(pidIdx);
  double motorOutput = m_primaryTalonElevator->GetMotorOutputPercent();
  int velocity = m_primaryTalonElevator->GetSelectedSensorVelocity(pidIdx);
  // std::cout << "Elevator current position: " << pos
    // << ", motor output: " << motorOutput
    // << ", sensor velocity: " << velocity
    // << ", error " << err << "\n";
	return m_primaryTalonElevator->GetClosedLoopError(pidIdx) < 250;
}

void Elevator::setHomePosition()
{
  // std::cout << "Elevator setting home position " << std::endl;
	//DriverStation::ReportWarning("Elevator home position reset");
	m_setpoint = 0;
  m_primaryTalonElevator->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
}

bool Elevator::atLowerLimit() {
  return m_primaryTalonElevator->GetSensorCollection().IsRevLimitSwitchClosed();
}

void Elevator::extend() {
  m_elevatorExtenderSolenoid->Set(true);
  m_elevatorRetracterSolenoid->Set(false);
  m_isRetracted = false;
}

void Elevator::retract() {
  m_elevatorExtenderSolenoid->Set(false);
  m_elevatorRetracterSolenoid->Set(true);
  m_isRetracted = true;
}

void Elevator::holdCurrentDeployment() {
  m_elevatorExtenderSolenoid->Set(false);
  m_elevatorRetracterSolenoid->Set(false);
}

bool Elevator::isRetracted() {
  return m_isRetracted;
}

int Elevator::getSelectedSensorPosition() {
  return m_primaryTalonElevator->GetSelectedSensorPosition(pidIdx);
}

int Elevator::getClosedLoopError() {
  return m_primaryTalonElevator->GetClosedLoopError(pidIdx);
}

double Elevator::getPGainValue() {
  return pGain;
}

  void Elevator::enableForwardLimitSwitch() {
      m_primaryTalonElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);
  }
  void Elevator::disableForwardLimitSwitch() {
      m_primaryTalonElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_Deactivated, LimitSwitchNormal_NormallyOpen, 0);
  }
  void Elevator::enableReverseLimitSwitch() {
      m_primaryTalonElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);
  }
  void Elevator::disableReverseLimitSwitch() {
      m_primaryTalonElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_Deactivated, LimitSwitchNormal_NormallyOpen, 0);
  }