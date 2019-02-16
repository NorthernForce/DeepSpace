/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>

class Elevator : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<WPI_TalonSRX> m_primaryTalonElevator;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator1;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator2;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator3;
 public:
  Elevator();
  void Raise();
  void Lower();
  void InitDefaultCommand() override;
};
