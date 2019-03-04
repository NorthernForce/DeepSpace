/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <frc/Timer.h>
#include <rev/CANSparkMax.h>

class CargoManipulator : public frc::Subsystem {
 public:
  constexpr static double k_ejectSpeed = -1.0;
  constexpr static double k_intakeSpeed = 0.7;

  // Duration in micro seconds
  constexpr static int k_divideSpeedDuration = 200 * 1000;
  constexpr static double k_divideSpeedAmount = 0.5;

  CargoManipulator();
  void InitDefaultCommand() override;
  void Periodic() override;
  void setSpeed(double speed);

 private:
  std::shared_ptr<rev::CANSparkMax> m_motor;

  std::shared_ptr<frc::Timer> m_divideSpeedTimer;
  bool m_divideSpeedTimerReset = true;

  constexpr static double k_rampRate = 0.2;
  constexpr static double k_secondaryCurrentLimit = 16.0;
  constexpr static int k_currentLimit = 8;
};
