/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GotoTarget.h"

#include "Robot.h"

#include "commands/LineTrackerFollowLine.h"
#include "commands/VisionFollowTarget.h"

GotoTarget::GotoTarget() : Command("GotoTarget") {
  m_followLine = new LineTrackerFollowLine();
  m_followReflectiveTape = new VisionFollowTarget("Targeter", "ReflectiveTape");
}

// Called just before this Command runs the first time
void GotoTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void GotoTarget::Execute() {
  if (Robot::m_lineTracker->getLineSensors() != 0) {
    if (!m_followLine->IsRunning()) {
      m_followReflectiveTape->Cancel();
      m_followLine->Start();
    }
  }
  else {
    if (!m_followReflectiveTape->IsRunning()) {
      m_followLine->Cancel();
      m_followReflectiveTape->Start();
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool GotoTarget::IsFinished() { return false; }

// Called once after isFinished returns true
void GotoTarget::End() {
  m_followLine->Cancel();
  m_followReflectiveTape->Cancel();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GotoTarget::Interrupted() { End(); }
