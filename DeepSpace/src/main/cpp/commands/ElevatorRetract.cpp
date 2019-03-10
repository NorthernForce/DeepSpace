/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorRetract.h"
#include "Robot.h"
#include "RobotMap.h"

ElevatorRetract::ElevatorRetract() : frc::TimedCommand(Elevator::k_deployDelay) {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorRetract::Initialize() {
  Robot::m_elevator->retract();
}