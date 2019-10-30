/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorCalibrate.h"

#include "Robot.h"

const double ElevatorCalibrate::k_highSpeed = -0.5;
const double ElevatorCalibrate::k_lowSpeed = -0.4;
const double ElevatorCalibrate::k_speedThreshold = 1500;
bool ElevatorCalibrate::k_calibrateDone;

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
  if (Robot::m_elevator->getSelectedSensorPosition() > k_speedThreshold) {
    Robot::m_elevator->setSpeed(k_highSpeed);
  }
  else {
    Robot::m_elevator->setSpeed(k_lowSpeed);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorCalibrate::IsFinished() { 
  return Robot::m_elevator->atLowerLimit() && !Robot::m_elevator->isRetracted();
}

// Called once after isFinished returns true
void ElevatorCalibrate::End() {
  Robot::m_elevator->stop();

  if (ElevatorCalibrate::k_calibrateDone == false) 
  {
    Robot::m_elevator->setHomePosition();
    ElevatorCalibrate::k_calibrateDone = true;
  }
  
  // This is now done in the elevator periodic
  // if (Robot::m_elevator->atLowerLimit()) {
  // }
  Robot::m_elevator->disableReverseLimitSwitch();
  Robot::m_elevator->disableForwardLimitSwitch();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorCalibrate::Interrupted() { End(); }
