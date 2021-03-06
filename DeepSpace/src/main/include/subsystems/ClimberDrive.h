/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "ctre/Phoenix.h"

class ClimberDrive : public frc::Subsystem {
 private:
  std::shared_ptr<WPI_TalonSRX> m_masterTalonWheels;

 public:
  ClimberDrive();
  void InitDefaultCommand() override;
  void setSpeed(double speed);
  void stop();

  const static double k_speedForward;
  const static double k_speedBackward;
  const static double k_speedIdle;

  const static double k_stopDelay;
};
