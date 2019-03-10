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
  const static double k_ejectSpeed;
  const static double k_intakeSpeed;

  const static int k_divideSpeedDuration;
  const static double k_divideSpeedAmount;

  const static double k_rampRate;
  const static double k_secondaryCurrentLimit;
  const static int k_currentLimit;

  CargoManipulator();
  void InitDefaultCommand() override;
  void Periodic() override;
  void setSpeed(double speed);

 private:
  std::shared_ptr<rev::CANSparkMax> m_motor;

  std::shared_ptr<frc::Timer> m_divideSpeedTimer;
  bool m_divideSpeedTimerReset = true;
};
