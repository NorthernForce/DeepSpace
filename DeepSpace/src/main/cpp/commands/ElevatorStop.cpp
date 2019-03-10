/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorStop.h"

#include "Robot.h"

ElevatorStop::ElevatorStop() : TimedCommand(Elevator::k_motorStopDelay) {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorStop::Initialize() {
  Robot::m_elevator->stop();
}