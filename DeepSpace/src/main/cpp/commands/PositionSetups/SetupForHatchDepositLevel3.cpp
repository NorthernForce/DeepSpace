/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionSetups/SetupForHatchDepositLevel3.h"

#include "commands/ElevatorSetPosition.h"
#include "commands/ClawOpen.h"
#include "commands/ClawLower.h"

SetupForHatchDepositLevel3::SetupForHatchDepositLevel3() {
  AddParallel(new ElevatorSetPosition(ElevatorSetPosition::Position::HatchDepositLevel3));
  AddSequential(new ClawOpen());
  AddSequential(new ClawLower());
}
