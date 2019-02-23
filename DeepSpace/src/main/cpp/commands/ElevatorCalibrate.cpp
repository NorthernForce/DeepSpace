/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorCalibrate.h"

#include "Robot.h"

ElevatorCalibrate::ElevatorCalibrate() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorCalibrate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorCalibrate::Execute() {
  Robot::m_elevator->Lower();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorCalibrate::IsFinished() { 
  return Robot::m_elevator->AtLowerLimit();
 }

// Called once after isFinished returns true
void ElevatorCalibrate::End() {
  if (Robot::m_elevator->AtLowerLimit()) {
    Robot::m_elevator->SetHomePosition();
  }
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorCalibrate::Interrupted() {}
