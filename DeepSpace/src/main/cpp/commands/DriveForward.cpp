/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveForward.h"
#include "Robot.h"

const double DriveForward::k_speed = 0.5; 
const double DriveForward::k_rotation = 0.0;

DriveForward::DriveForward() {
  Requires(Robot::m_driveTrain.get());
}

// Called just before this Command runs the first time
void DriveForward::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
  Robot::m_driveTrain->arcDrive(k_speed, k_rotation);
} 

// Make this return true when this Command no longer needs to run execute()
bool DriveForward::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveForward::End() {
  Robot::m_driveTrain->arcDrive(0.0, k_rotation);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForward::Interrupted() { End(); }
