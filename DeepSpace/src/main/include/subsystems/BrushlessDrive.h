/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Drive/DifferentialDrive.h>
#include <rev/CANSparkMax.h>

class BrushlessDrive : public frc::Subsystem {
 public:
  BrushlessDrive();
  void InitDefaultCommand() override;
  void arcDrive(double speed, double rotation);

  const static double k_rampRate;
  const static double k_secondaryCurrentLimit;
  const static int k_currentLimit;

 private:
  void ConfigureController(rev::CANSparkMax& controller);

  std::shared_ptr<rev::CANSparkMax>        m_leftPrimaryBrushless;
  std::shared_ptr<rev::CANSparkMax>        m_leftFollowerBrushless;

  std::shared_ptr<rev::CANSparkMax>        m_rightPrimaryBrushless;
  std::shared_ptr<rev::CANSparkMax>        m_rightFollowerBrushless;

  std::shared_ptr<frc::DifferentialDrive>  m_robotBrushlessDrive;
};
