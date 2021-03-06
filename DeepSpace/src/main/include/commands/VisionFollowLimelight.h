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

class VisionFollowLimelight : public frc::Command {
 public:
  VisionFollowLimelight();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  const static double k_p;
  const static double k_i;
  const static double k_d;

  const static double k_maxTurnSpeed;

  const static double k_targetOffset;

  const static double k_areaEffecter;
  const static double k_maxArea;

  double m_error = 0;
  double m_error_prior = 0;
  double m_integral = 0;
  double m_derivative = 0;
};
