/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

#include <ctre/Phoenix.h>

#include "RobotMap.h"
#include <iostream>

Elevator::Elevator() : Subsystem("Elevator") { 
  
    m_primaryTalonElevator.reset(new WPI_TalonSRX (RobotMap::Elevator::k_primary_id));
    m_followerTalonElevator1.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower1_id));
    m_followerTalonElevator2.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower2_id));
    m_followerTalonElevator3.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower3_id));
    m_elevatorExtenderSolenoid.reset(new frc::Solenoid (RobotMap::PCM::k_pcm_id, RobotMap::Elevator::k_solenoid_id));

    m_followerTalonElevator1->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator2->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator3->Follow(*m_primaryTalonElevator);

    m_primaryTalonElevator->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);
    m_primaryTalonElevator->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

    //m_primaryTalonElevator->SetSensorPhase(true);
    m_primaryTalonElevator->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, pidIdx, 10);


    /* Set relevant frame periods to be at least as fast as periodic rate */
    m_primaryTalonElevator->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    m_primaryTalonElevator->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    /* Set the peak and nominal outputs */
    m_primaryTalonElevator->ConfigNominalOutputForward(0, 10);
    m_primaryTalonElevator->ConfigNominalOutputReverse(0, 10);
    m_primaryTalonElevator->ConfigPeakOutputForward(.8, 10);
    m_primaryTalonElevator->ConfigPeakOutputReverse(-.5, 10);

    /* Set Motion Magic gains in slot0 - see documentation */
    m_primaryTalonElevator->SelectProfileSlot(0, pidIdx);
    m_primaryTalonElevator->Config_kF(pidIdx, 0.0, 10);
    m_primaryTalonElevator->Config_kP(pidIdx, pGain, 10);
    m_primaryTalonElevator->Config_kI(pidIdx, iGain, 10);
    m_primaryTalonElevator->Config_kD(pidIdx, 0.0, 10);
    m_primaryTalonElevator->ConfigMaxIntegralAccumulator(pidIdx, iLimit, timeoutMs);
    m_primaryTalonElevator->ConfigOpenloopRamp(rampTime);
    m_primaryTalonElevator->ConfigClosedloopRamp(rampTime);

    /* Set acceleration and vcruise velocity - see documentation */
    m_primaryTalonElevator->ConfigMotionCruiseVelocity(1500, 10);
    m_primaryTalonElevator->ConfigMotionAcceleration(1500, 10);

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


}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void Elevator::Raise(){
   m_primaryTalonElevator->Set(RobotMap::Elevator::k_elevatorRaiseSpeed);

//Elevator has 3 floors
}
void Elevator::Lower(){
   m_primaryTalonElevator->Set(RobotMap::Elevator::k_elevatorLowerSpeed);

  //Elevator has 3 floors 
}

void Elevator::Stop() {
  m_primaryTalonElevator->Set(0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands

void Elevator::SetPosition(int setpoint)
{
  
  // std::cout << "Elevator set position to " << setpoint << std::endl;
	m_setpoint = setpoint;
  // std::cout << "Elevator set position to " << setpoint << " with magic" << std::endl;
	m_primaryTalonElevator->Set(ControlMode::Position, m_setpoint);
}

bool Elevator::AtSetpoint()
{
  int pos = m_primaryTalonElevator->GetSelectedSensorPosition(pidIdx);
  int err = m_primaryTalonElevator->GetClosedLoopError(0);
    double motorOutput = m_primaryTalonElevator->GetMotorOutputPercent();
  int velocity = m_primaryTalonElevator->GetSelectedSensorVelocity(pidIdx);
  // std::cout << "Elevator current position: " << pos
    // << ", motor output: " << motorOutput
    // << ", sensor velocity: " << velocity
    // << ", error " << err << "\n";
	return m_primaryTalonElevator->GetClosedLoopError(0) < 100;
}

void Elevator::SetHomePosition()
{
  // std::cout << "Elevator setting home position " << std::endl;
	//DriverStation::ReportWarning("Elevator home position reset");
	m_setpoint = 0;
  m_primaryTalonElevator->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
}

bool Elevator::AtLowerLimit() {
  return m_primaryTalonElevator->GetSensorCollection().IsRevLimitSwitchClosed();
}

void Elevator::Extend(){
  m_elevatorExtenderSolenoid->Set(RobotMap::Elevator::k_elevatorExtendedValue);
}

void Elevator::Retract(){
  m_elevatorExtenderSolenoid->Set(RobotMap::Elevator::k_elevatorRetractedValue);
}

int Elevator::GetSelectedSensorPosition() {
  return m_primaryTalonElevator->GetSelectedSensorPosition(0);
}

int Elevator::GetClosedLoopError() {
  return m_primaryTalonElevator->GetClosedLoopError(0);
}