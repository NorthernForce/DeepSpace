/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSetup.h"

#include "commands/ElevatorExtend.h"
#include "commands/ElevatorCalibrate.h"

ElevatorSetup::ElevatorSetup() : CommandGroup("ElevatorSetup") {
  AddSequential(new ElevatorExtend());
  AddSequential(new ElevatorCalibrate());
}
