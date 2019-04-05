/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BrushlessDrive.h"

#include "RobotMap.h"
#include "commands/DriveWithJoystick.h"

#include <frc/smartdashboard/SmartDashboard.h>

const double BrushlessDrive::k_rampRate = 0.2;
const double BrushlessDrive::k_secondaryCurrentLimit = 80.0;
const int BrushlessDrive::k_currentLimit = 50;

BrushlessDrive::BrushlessDrive() : Subsystem("BrushlessDrive") {
  // Left Side
  m_leftPrimaryBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_leftPrimary_id, rev::CANSparkMax::MotorType::kBrushless));

  m_leftFollowerBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_leftFollower_id, rev::CANSparkMax::MotorType::kBrushless));
  m_leftFollowerBrushless->Follow(*m_leftPrimaryBrushless);

  // Right Side
  m_rightPrimaryBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_rightPrimary_id, rev::CANSparkMax::MotorType::kBrushless));

  m_rightFollowerBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_rightFollower_id, rev::CANSparkMax::MotorType::kBrushless));
  m_rightFollowerBrushless->Follow(*m_rightPrimaryBrushless);

  // Initialize the drive.
  m_robotBrushlessDrive.reset(new frc::DifferentialDrive(*m_leftPrimaryBrushless, *m_rightPrimaryBrushless));

  ConfigureController(*m_leftPrimaryBrushless);
  ConfigureController(*m_leftFollowerBrushless);
  ConfigureController(*m_rightPrimaryBrushless);
  ConfigureController(*m_rightFollowerBrushless);
  
  // frc::SmartDashboard::PutNumber("BrushlessDrive: Spark1 Temp: ", -1);
  // frc::SmartDashboard::PutNumber("BrushlessDrive: Spark3 Temp: ", -1);
  // frc::SmartDashboard::PutNumber("BrushlessDrive: Spark2 Temp: ", -1);
  // frc::SmartDashboard::PutNumber("BrushlessDrive: Spark4 Temp: ", -1);
}

void BrushlessDrive::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  SetDefaultCommand(new DriveWithJoystick());
}

void BrushlessDrive::Periodic() {
  // double spark1new = m_leftPrimaryBrushless->GetMotorTemperature();
  // double spark3new = m_leftFollowerBrushless->GetMotorTemperature();
  // double spark2new = m_rightPrimaryBrushless->GetMotorTemperature();
  // double spark4new = m_rightFollowerBrushless->GetMotorTemperature();

  // if (frc::SmartDashboard::GetNumber("BrushlessDrive: Spark1 Temp", -1) < spark1new) {
  //   frc::SmartDashboard::PutNumber("BrushlessDrive: Spark1 Temp", spark1new);
  // }

  // if (frc::SmartDashboard::GetNumber("BrushlessDrive: Spark2 Temp", -1) < spark2new) {
  //   frc::SmartDashboard::PutNumber("BrushlessDrive: Spark2 Temp", spark2new);
  // }

  // if (frc::SmartDashboard::GetNumber("BrushlessDrive: Spark3 Temp", -1) < spark3new) {
  //   frc::SmartDashboard::PutNumber("BrushlessDrive: Spark3 Temp", spark3new);
  // }

  // if (frc::SmartDashboard::GetNumber("BrushlessDrive: Spark4 Temp", -1) < spark1new) {
  //   frc::SmartDashboard::PutNumber("BrushlessDrive: Spark4 Temp", spark1new);
  // }
}

void BrushlessDrive::arcDrive(double speed, double rotation)
{
  m_robotBrushlessDrive->ArcadeDrive(speed, rotation);
}

void BrushlessDrive::ConfigureController(rev::CANSparkMax& controller)
{
  controller.SetSecondaryCurrentLimit(k_secondaryCurrentLimit);
  controller.SetSmartCurrentLimit(k_currentLimit);
  if(!controller.IsFollower())
  {
    controller.SetClosedLoopRampRate(k_rampRate);
    controller.SetOpenLoopRampRate(k_rampRate);
  }
  controller.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}
