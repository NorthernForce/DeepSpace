/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ToggleElevatorDeployment.h"

#include "Robot.h"

ToggleElevatorDeployment::ToggleElevatorDeployment() : TimedCommand(k_duration) {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ToggleElevatorDeployment::Initialize() {
  if (Robot::m_elevator->IsRetracted()) {
    Robot::m_elevator->Extend();
  }
  else {
    Robot::m_elevator->Retract();
  }
}
