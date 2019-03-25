/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LineTracker.h"

LineTracker::LineTracker() : Subsystem("LineTracker") {
  m_lineSensorCenter.reset(new frc::DigitalInput(RobotMap::LineTracker::k_centerLineSensor_id));
  m_lineSensorLeft.reset(new frc::DigitalInput(RobotMap::LineTracker::k_leftLineSensor_id));
  m_lineSensorRight.reset(new frc::DigitalInput(RobotMap::LineTracker::k_rightLineSensor_id));
}

void LineTracker::InitDefaultCommand() {}

int LineTracker::getLineSensors() {
  int left = m_lineSensorLeft->Get() ? 0 : 0b100;
  int center = m_lineSensorCenter->Get() ? 0 : 0b010;
  int right = m_lineSensorRight->Get() ? 0 : 0b001;
  
  return left | center | right; 
}

