/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForCargoDepositLevel1.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/CloseClaw.h"
#include "commands/RaiseClaw.h"

SetupForCargoDepositLevel1::SetupForCargoDepositLevel1() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::CargoDepositLevel1));
  AddParallel(new RaiseClaw());
  AddParallel(new CloseClaw());
}
