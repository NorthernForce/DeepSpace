/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

class ClimbEvenlyUp : public frc::Command {
 public:
  ClimbEvenlyUp();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
  
  const static double k_maxFrontTilt;
  const static double k_maxBackTilt;
  const static double k_targetTilt;

 private:
  bool m_climbingStarted = false;
};
