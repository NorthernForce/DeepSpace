/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>

#include "subsystems/IndicatorLights/Effect.h"

class IndicatorLightsEffect : public frc::Command {
 public:
  IndicatorLightsEffect(std::shared_ptr<IndicatorLights::Effect> effect = nullptr);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  std::shared_ptr<IndicatorLights::Effect> m_effect;
};
