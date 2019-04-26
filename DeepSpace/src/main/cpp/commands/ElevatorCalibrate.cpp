/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorCalibrate.h"

#include "Robot.h"

const double ElevatorCalibrate::k_lowerSpeed = -0.4;

ElevatorCalibrate::ElevatorCalibrate() : Command("ElevatorCalibrate") {
  Requires(Robot::m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorCalibrate::Initialize() {
  Robot::m_elevator->enableReverseLimitSwitch();
  Robot::m_elevator->enableForwardLimitSwitch();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorCalibrate::Execute() {
  Robot::m_elevator->setSpeed(k_lowerSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorCalibrate::IsFinished() { 
  return Robot::m_elevator->atLowerLimit() && !Robot::m_elevator->isRetracted();
}

// Called once after isFinished returns true
void ElevatorCalibrate::End() {
  Robot::m_elevator->stop();
  
  // This is now done in the elevator periodic
  // if (Robot::m_elevator->atLowerLimit()) {
  //   Robot::m_elevator->setHomePosition();
  // }
  Robot::m_elevator->disableReverseLimitSwitch();
  Robot::m_elevator->disableForwardLimitSwitch();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorCalibrate::Interrupted() { End(); }
