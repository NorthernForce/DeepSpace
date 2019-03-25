/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LineTrackerFollowLine.h"

#include "Robot.h"
#include "RobotMap.h"

const double LineTrackerFollowLine::k_turnSpeed = 0.2;

LineTrackerFollowLine::LineTrackerFollowLine() {
  Requires(Robot::m_lineTracker.get());
  Requires(Robot::m_driveTrain.get());
}

// Called just before this Command runs the first time
void LineTrackerFollowLine::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LineTrackerFollowLine::Execute() {
  double rotation = 0;

  switch(Robot::m_lineTracker->getLineSensors()) {
    case 0b001: // Right Sensor Detected Line; Turn right
      rotation = k_turnSpeed;
      break;
    case 0b011: // Right & Center Sensor Detected Line; Turn right
      rotation = k_turnSpeed;
      break;
    case 0b100: // Left Sensor Detected Line; Turn Left
      rotation = k_turnSpeed * -1;
      break;
    case 0b110: // Left & Center Sensor Detected Line; Turn left
      rotation = k_turnSpeed * -1;
      break;
  }

  Robot::m_driveTrain->arcDrive(Robot::m_oi->getSteeringControls().first, rotation);
}

// Make this return true when this Command no longer needs to run execute()
bool LineTrackerFollowLine::IsFinished() { return false; }

// Called once after isFinished returns true
void LineTrackerFollowLine::End() {
  Robot::m_driveTrain->arcDrive(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LineTrackerFollowLine::Interrupted() { End(); }