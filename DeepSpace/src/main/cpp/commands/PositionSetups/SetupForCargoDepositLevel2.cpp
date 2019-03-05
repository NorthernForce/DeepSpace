/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForCargoDepositLevel2.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/CloseClaw.h"
#include "commands/RaiseClaw.h"

SetupForCargoDepositLevel2::SetupForCargoDepositLevel2() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::CargoDepositLevel2));
  AddSequential(new RaiseClaw());
  AddSequential(new CloseClaw());
}
