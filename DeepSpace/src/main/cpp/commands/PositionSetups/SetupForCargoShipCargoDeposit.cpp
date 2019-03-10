/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForCargoShipCargoDeposit.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/ClawClose.h"
#include "commands/ClawRaise.h"

SetupForCargoShipCargoDeposit::SetupForCargoShipCargoDeposit() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::CargoShipCargoDeposit));
  AddSequential(new ClawRaise());
  AddSequential(new ClawClose());
}
