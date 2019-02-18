/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FollowLine.h"
#include "Robot.h"
#include "RobotMap.h"

FollowLine::FollowLine() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::m_lineTracker.get());
  Requires(Robot::m_driveTrain.get());
  Requires(Robot::m_ultrasonic.get());
}

// Called just before this Command runs the first time
void FollowLine::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FollowLine::Execute() {
  m_faultyCase = false;
  m_stopRobot = false;

  switch(Robot::m_lineTracker->GetLineSensors())
  {
    case 0b000: //No Line Detected
      m_faultyCase = true;
      break;
    case 0b001: //Right Sensor Detected Line; Turn Right
      speed = 0.7;
      rotation = 0.4;
      break;
    case 0b010: //Center Sensor Detected Line; Don't Turn
      speed = 0.7;
      rotation = 0;
      break;
    case 0b011: //Right & Center Sensor Detected Line; Turn Left Less
      speed = 0.7;
      rotation = -0.2;
      break;
    case 0b100: //Left Sensor Detected Line; Turn Left
      speed = 0.7;
      rotation = -0.4;
      break;
    case 0b101: //Should not happen; Stop
      m_faultyCase = true;
      break;
    case 0b110: //Left & Center Sensor Detected Line; Turn Right Less
      speed = 0.7;
      rotation = 0.2;
      break;
    case 0b111: //Line on All Three Sensors; Stop Command
      m_faultyCase = true;
      break;
  }

  Robot::m_driveTrain->arcDrive(speed, rotation); //12 inch an 13 inch for ball and hatch respectively

  if (m_faultyCase = true || Robot::m_ultrasonic->GetDistanceToWall() < 14) {
    m_stopRobot = true;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool FollowLine::IsFinished() {
  return m_stopRobot;
}

// Called once after isFinished returns true
void FollowLine::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowLine::Interrupted() {}
