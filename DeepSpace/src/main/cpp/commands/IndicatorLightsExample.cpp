/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IndicatorLightsExample.h"

#include "Robot.h"

IndicatorLightsExample::IndicatorLightsExample() {
  Requires(Robot::m_indicatorLights.get());
}

// Called just before this Command runs the first time
void IndicatorLightsExample::Initialize() {
  std::vector<std::vector<uint8_t>> colors(4, std::vector<uint8_t>{0, 255, 0});

  Robot::m_indicatorLights->assembleFrame(colors);
}

// Called repeatedly when this Command is scheduled to run
void IndicatorLightsExample::Execute() {
  Robot::m_indicatorLights->sendFrame();
}

// Make this return true when this Command no longer needs to run execute()
bool IndicatorLightsExample::IsFinished() { return false; }

// Called once after isFinished returns true
void IndicatorLightsExample::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IndicatorLightsExample::Interrupted() {}
