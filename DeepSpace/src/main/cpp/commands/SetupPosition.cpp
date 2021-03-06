/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetupPosition.h"

#include "commands/ClawOpen.h"
#include "commands/ClawClose.h"
#include "commands/ClawLower.h"
#include "commands/ClawRaise.h"
#include "commands/CargoSetIdle.h"

SetupPosition::SetupPosition(ElevatorSetPosition::Position position, TargetType type) : CommandGroup("SetupPosition") {
  AddParallel(new ElevatorSetPosition(position));

  if (type == TargetType::Cargo) {
    AddSequential(new CargoSetIdle(true));
    AddSequential(new ClawRaise());
    AddSequential(new ClawClose());
  }
  else if (type == TargetType::Hatch) {
    AddSequential(new CargoSetIdle(false));
    AddSequential(new ClawLower());
    AddSequential(new ClawOpen());
  }
}
