/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IndicatorLightsExample.h"

#include "subsystems/IndicatorLights/Pulse.h"
#include "subsystems/IndicatorLights/Solid.h"

#include "Robot.h"

IndicatorLightsExample::IndicatorLightsExample() {
  // Requires(Robot::m_indicatorLights.get());
}

// Called just before this Command runs the first time
void IndicatorLightsExample::Initialize() {
  Robot::m_indicatorLights->setEffect(std::make_shared<IndicatorLights::Pulse>(std::vector<uint8_t>{255, 0, 0}, 0.02));
}

// Called repeatedly when this Command is scheduled to run
void IndicatorLightsExample::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool IndicatorLightsExample::IsFinished() { return true; }

// Called once after isFinished returns true
void IndicatorLightsExample::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IndicatorLightsExample::Interrupted() {}
