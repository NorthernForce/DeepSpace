/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BrushlessDrive.h"

#include "../include/RobotMap.h"

BrushlessDrive::BrushlessDrive() : Subsystem("ExampleSubsystem") {
  // Left Side
  m_leftPrimaryBrushless.reset(new rev::CANSparkMax(k_leftPrimaryBrushlessDrive_id, rev::CANSparkMax::MotorType::kBrushless));

  m_leftFollowerBrushless.reset(new rev::CANSparkMax(k_leftFollowerBrushlessDrive_id, rev::CANSparkMax::MotorType::kBrushless));
  m_leftFollowerBrushless->Follow(*m_leftPrimaryBrushless);

  // Right Side
  m_rightPrimaryBrushless.reset(new rev::CANSparkMax(k_rightPrimaryBrushlessDrive_id, rev::CANSparkMax::MotorType::kBrushless));

  m_rightFollowerBrushless.reset(new rev::CANSparkMax(k_rightFollowerBrushlessDrive_id, rev::CANSparkMax::MotorType::kBrushless));
  m_rightFollowerBrushless->Follow(*m_rightFollowerBrushless);

  // Invert a side
  m_leftPrimaryBrushless->SetInverted(true);
  m_rightPrimaryBrushless->SetInverted(true);
}

void BrushlessDrive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void BrushlessDrive::arcDrive(int y, int x)
{
   m_robotBrushlessDrive->ArcadeDrive(y, x);
}