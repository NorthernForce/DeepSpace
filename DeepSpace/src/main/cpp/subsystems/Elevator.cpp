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

    m_followerTalonElevator1->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator2->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator3->Follow(*m_primaryTalonElevator);

    m_primaryTalonElevator->SetSensorPhase(true);
    m_primaryTalonElevator->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);


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
// Put methods for controlling this subsystem
// here. Call these from Commands

void Elevator::SetPosition(int setpoint)
{
  
  std::cout << "Elevator set position to " << setpoint << std::endl;
	m_setpoint = setpoint;
  std::cout << "Elevator set position to " << setpoint << " with motion magic" << std::endl;
	m_primaryTalonElevator->Set(ControlMode::MotionMagic, m_setpoint);
}

bool Elevator::AtSetpoint()
{
  int pos = m_primaryTalonElevator->GetSelectedSensorPosition();
  int err = m_primaryTalonElevator->GetClosedLoopError(pidIdx);
    double motorOutput = m_primaryTalonElevator->GetMotorOutputPercent();
  int velocity = m_primaryTalonElevator->GetSelectedSensorVelocity(0);
  std::cout << "Elevator current position: " << pos 
    << ", motor output: " << motorOutput
    << ", motor velocity: " << velocity
    << ", error " << err << std::endl;
	return m_primaryTalonElevator->GetClosedLoopError(pidIdx) < 250;
}

void Elevator::SetHomePosition()
{
  std::cout << "Elevator setting home position " << std::endl;
	//DriverStation::ReportWarning("Elevator home position reset");
	m_setpoint = 0;
  m_primaryTalonElevator->SetSelectedSensorPosition(m_setpoint, pidIdx, timeoutMs);
  m_primaryTalonElevator->Set(ControlMode::MotionMagic, m_setpoint);
}