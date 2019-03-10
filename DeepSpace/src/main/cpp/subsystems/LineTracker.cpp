/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LineTracker.h"

LineTracker::LineTracker() : Subsystem("LineTracker") {
  m_lineSensorCenter.reset(new frc::DigitalInput(RobotMap::LineTracker::k_CenterLineSensor_id));
  m_lineSensorLeft.reset(new frc::DigitalInput(RobotMap::LineTracker::k_leftLineSensor_id));
  m_lineSensorRight.reset(new frc::DigitalInput(RobotMap::LineTracker::k_RightLineSensor_id));

}

void LineTracker::InitDefaultCommand() {}

int LineTracker::getLineSensors() {
  int left = m_lineSensorLeft->Get() ? 0b100 : 0;
  int center = m_lineSensorCenter->Get() ? 0b010 : 0;
  int right = m_lineSensorRight->Get() ? 0b001 : 0;
  
  return left + center + right; 
}



// Put methods for controlling this subsystem
// here. Call these from Commands.
