/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IndicatorLightsEffect.h"

#include "Robot.h"

IndicatorLightsEffect::IndicatorLightsEffect(std::shared_ptr<IndicatorLights::Effect> effect) {
  // Requires(Robot::m_indicatorLights.get());
  m_effect = effect;
}

// Called just before this Command runs the first time
void IndicatorLightsEffect::Initialize() {
  Robot::m_indicatorLights->setEffect(m_effect);
}

// Called repeatedly when this Command is scheduled to run
void IndicatorLightsEffect::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool IndicatorLightsEffect::IsFinished() { return true; }

// Called once after isFinished returns true
void IndicatorLightsEffect::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IndicatorLightsEffect::Interrupted() {}
