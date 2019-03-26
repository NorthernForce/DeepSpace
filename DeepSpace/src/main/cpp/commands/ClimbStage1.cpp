/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbStage1.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/ClimberLower.h"

ClimbStage1::ClimbStage1() : CommandGroup("ClimbStage1") {
  AddParallel(new ClimberLower());
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::HomePosition));
}
