/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/RangeFinder.h"
#include "RobotMap.h"

RangeFinder::RangeFinder() : Subsystem("RangeFinder") 
{
   m_ctrl.reset(new frc::DigitalOutput(RobotMap::Ultrasonic::k_digitalCtlPort));
   m_voltageReader.reset(new frc::AnalogInput(RobotMap::Ultrasonic::k_analogPort));
   m_ctrl->Set( RobotMap::Ultrasonic::k_ultrasonicOn );
}


void RangeFinder::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


double RangeFinder::getDistance()
{
  m_voltage = m_voltageReader->GetVoltage();
  m_rangeInches = (m_voltage / 0.0098);
  return m_rangeInches;
}


int RangeFinder::enable()
{
  m_ctrl->Set( RobotMap::Ultrasonic::k_ultrasonicOn );
  return 0;
}


int RangeFinder::disable()
{
  m_ctrl->Set( RobotMap::Ultrasonic::k_ultrasonicOff );
  return 0;
}