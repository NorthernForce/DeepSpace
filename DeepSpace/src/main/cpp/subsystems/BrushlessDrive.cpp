/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BrushlessDrive.h"

#include "RobotMap.h"

#include "commands/DriveWithJoystick.h"

BrushlessDrive::BrushlessDrive() : Subsystem("BrushlessDrive") {
  // Left Side
  m_leftPrimaryBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_leftPrimary_id, rev::CANSparkMax::MotorType::kBrushless));

  m_leftFollowerBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_leftFollower_id, rev::CANSparkMax::MotorType::kBrushless));
  m_leftFollowerBrushless->Follow(*m_leftPrimaryBrushless);

  // Right Side
  m_rightPrimaryBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_rightPrimary_id, rev::CANSparkMax::MotorType::kBrushless));

  m_rightFollowerBrushless.reset(new rev::CANSparkMax(RobotMap::BrushlessDrive::k_rightFollower_id, rev::CANSparkMax::MotorType::kBrushless));
  m_rightFollowerBrushless->Follow(*m_rightPrimaryBrushless);

  // Invert a side
  // m_leftPrimaryBrushless->SetInverted(false);
  // m_rightPrimaryBrushless->SetInverted(true);

  // Initialize the drive.
  m_robotBrushlessDrive.reset(new frc::DifferentialDrive(*m_leftPrimaryBrushless, *m_rightPrimaryBrushless));
}

void BrushlessDrive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new DriveWithJoystick());
}

void BrushlessDrive::arcDrive(double y, double x)
{
  m_robotBrushlessDrive->ArcadeDrive(y, x);
}