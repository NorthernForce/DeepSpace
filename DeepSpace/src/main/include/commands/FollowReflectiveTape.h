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

  const static double k_p;
  const static double k_i;
  const static double k_d;

  const static double k_iterationTime;

 private:
  const std::string k_cameraName = "Elevator";
  const std::string k_targetName = "ReflectiveTape";

  double m_error = 0;
  double m_error_prior = 0;
  double m_integral = 0;
  double m_derivative = 0;
};
