/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>

class CargoManipulator : public frc::Subsystem {
 public:
  constexpr static double k_ejectSpeed = 1.0;
  constexpr static double k_intakeSpeed = 1.0;

  const static int k_continuousCurrent = 10;
  const static int k_peakCurrent = 25;
  const static int k_peakCurrentDuration = 1000;

  // Time in periodics
  const static int k_divideSpeedDuration = 4;
  constexpr static double k_divideSpeedAmount = 0.5;

  CargoManipulator();
  void InitDefaultCommand() override;
  void Periodic() override;
  void setSpeed(double speed);

 private:
  std::shared_ptr<WPI_TalonSRX> m_motor;

  int m_divideSpeedCount = 0;
};
