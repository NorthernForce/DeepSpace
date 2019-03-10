/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>

#include "commands/ElevatorSetPosition.h"

class SetupPosition : public frc::CommandGroup {
 public:
  enum class TargetType {
    None,
    Cargo,
    Hatch
  };

  SetupPosition(ElevatorSetPosition::Position position, TargetType type = TargetType::None);
};
