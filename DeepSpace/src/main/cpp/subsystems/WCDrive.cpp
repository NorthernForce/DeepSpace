/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/WCDrive.h"

#include "RobotMap.h"

WCDrive::WCDrive() : frc::Subsystem("WCDrive") 
{
  //Instantiate the Left Drive Motor(s)
  m_leftPrimaryTalon.reset(new WPI_TalonSRX(RobotMap::WCDrive::k_leftPrimary_id));

  //Instantiate the Right Drive Motor(s)
  m_rightPrimaryTalon.reset(new WPI_TalonSRX(RobotMap::WCDrive::k_rightPrimary_id));

  //Instantiate the Robot Drive
  m_robotWCDrive.reset(new frc::DifferentialDrive(*m_leftPrimaryTalon, *m_rightPrimaryTalon));
}

void WCDrive::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void WCDrive::arcDrive(double speed, double rotation)
{
   m_robotWCDrive->ArcadeDrive(speed, rotation);
}

