/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/WCDrive.h"

#include "../include/RobotMap.h"

WCDrive::WCDrive() : frc::Subsystem("WCDrive") 
{
  //Instantiate the Left Drive Motor(s)
  m_leftPrimaryTalon.reset(new WPI_TalonSRX(k_leftWCDrive_id));

  //Instantiate the Right Drive Motor(s)
  m_rightPrimaryTalon.reset(new WPI_TalonSRX(k_rightWCDrive_id));

  //Instantiate the Robot Drive
  m_robotWCDrive.reset(new frc::DifferentialDrive(*m_leftPrimaryTalon, *m_rightPrimaryTalon));

  m_leftPrimaryTalon->SetInverted(false);
  m_rightPrimaryTalon->SetInverted(true);

}

void WCDrive::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void WCDrive::arcDrive(int y, int x)
{
   m_robotWCDrive->ArcadeDrive(y, x);
}

