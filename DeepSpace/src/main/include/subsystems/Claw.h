/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"

#include <frc/Solenoid.h>

class Claw : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<frc::Solenoid> m_clawSolenoid;
  std::shared_ptr<frc::Solenoid> m_raiseSolenoid;
  enum class State {
		Raised,
		Lowered
	};
  State m_raisedState;

 public:
  Claw();
  void InitDefaultCommand() override;
  void open();
  void close();
  void raise();
  void lower();
  bool isRaised();

  const static bool k_clawOpenValue;
  const static bool k_clawClosedValue;
  const static bool k_clawRaisedValue;
  const static bool k_clawLoweredValue;

  const static double k_timeToOpen;
  const static double k_timeToClose;
  const static double k_timeToRaise;
  const static double k_timeToLower;
};
