/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/WCDrive.h"
//#include "../include/RobotMap.h"

WCDrive::WCDrive() : frc::Subsystem("WCDrive") 
{
  //Instantiate the Left Drive Motor(s)
  m_leftWCDrive  = new rev::CANSparkMax(k_leftWCDrive_ID, rev::CANSparkMax::MotorType::kBrushless);
  //Instantiate the Right Drive Motor(s)
  m_rightWCDrive = new rev::CANSparkMax(k_rightWCDrive_ID, rev::CANSparkMax::MotorType::kBrushless);
  //Instantiate the Robot Drive
  m_robotWCDrive = new frc::DifferentialDrive(*m_leftWCDrive, *m_rightWCDrive);

  m_rightWCDrive->SetInverted(true);
  m_leftWCDrive->SetInverted(false);

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
// Put methods for controlling this subsystem
// here. Call these from Commands.
