/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LightRing.h"
#include "RobotMap.h"

LightRing::LightRing() : Subsystem("LightRing") 
{
  m_Relay.reset(new frc::Relay(RobotMap::Camera::k_lightRingRelay, frc::Relay::kForwardOnly));

}


void LightRing::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


void LightRing::LightRingOn()
{
  m_Relay->Set(frc::Relay::kOn);
}


void LightRing::LightRingOff()
{
  m_Relay->Set(frc::Relay::kOff);
}