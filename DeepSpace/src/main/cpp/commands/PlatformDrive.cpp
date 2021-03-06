/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PlatformDrive.h"
#include "commands/ClimberDriveForward.h"
#include "commands/DriveForward.h"

PlatformDrive::PlatformDrive() : CommandGroup("PlatformDrive") {
  AddParallel(new ClimberDriveForward());
  //AddParallel(new DriveForward());
}
