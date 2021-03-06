/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorToggleDeployment.h"

#include "Robot.h"

ElevatorToggleDeployment::ElevatorToggleDeployment() : TimedCommand("ElevatorToggleDeployment", Elevator::k_deployDelay) {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorToggleDeployment::Initialize() {
  if (Robot::m_elevator->isRetracted()) {
    Robot::m_elevator->extend();
  }
  else {
    Robot::m_elevator->retract();
  }
}
