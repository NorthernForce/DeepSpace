/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForCargoDepositLevel3.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/ClawClose.h"
#include "commands/ClawRaise.h"

SetupForCargoDepositLevel3::SetupForCargoDepositLevel3() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::CargoDepositLevel3));
  AddSequential(new ClawRaise());
  AddSequential(new ClawClose());
}
