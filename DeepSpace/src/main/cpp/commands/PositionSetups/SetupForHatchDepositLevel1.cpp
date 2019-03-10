/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForHatchDepositLevel1.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/ClawOpen.h"
#include "commands/ClawLower.h"

SetupForHatchDepositLevel1::SetupForHatchDepositLevel1() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::HatchDepositLevel1));
  AddSequential(new ClawOpen());
  AddSequential(new ClawLower());
}
