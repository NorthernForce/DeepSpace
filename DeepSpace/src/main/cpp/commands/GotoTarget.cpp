/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/GotoTarget.h"

#include "Robot.h"

#include "commands/LineTrackerFollowLine.h"
#include "commands/VisionFollowReflectiveTape.h"

GotoTarget::GotoTarget() {
  m_followLine = new LineTrackerFollowLine();
  m_followReflectiveTape = new VisionFollowReflectiveTape();
}

// Called just before this Command runs the first time
void GotoTarget::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void GotoTarget::Execute() {
  std::cout << "muiyo " << Robot::m_lineTracker->getLineSensors() << " ";
  if (Robot::m_lineTracker->getLineSensors() != 0) {
    std::cout << "Here ";
    if (!m_followLine->IsRunning()) {
      std::cout << "yas" << "\n";
      m_followReflectiveTape->Cancel();
      m_followLine->Start();
    }
  }
  else {
    std::cout << " yeahyyey\n";
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
