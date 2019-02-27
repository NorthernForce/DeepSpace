/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/PIDController.h>

#include <string>

class FollowReflectiveTape : public frc::Command {
 public:
  FollowReflectiveTape();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  const double k_p = 0;
  const double k_i = 0;
  const double k_d = 0;

  const std::string k_cameraName = "Elevator";
  const std::string k_targetName = "ReflectiveTape";

  double m_error = 0;
  double m_error_prior = 0;
  double m_integral = 0;
  double m_derivative = 0;

  const double k_iterationTime = 0.02;
};
