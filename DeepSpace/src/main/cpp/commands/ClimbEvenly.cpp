/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbEvenly.h"
#include "Robot.h"

ClimbEvenly::ClimbEvenly() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::m_imu.get());
  Requires(Robot::m_elevator.get());
  Requires(Robot::m_climber.get());
}

// Called just before this Command runs the first time
void ClimbEvenly::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimbEvenly::Execute() {
  int tiltGain = 4; //Angle from 0-180 
  double tiltAngle = Robot::m_imu->getAngle();
  
  if ( tiltAngle > 5)
  {
    Robot::m_elevator->LowerExplicit(RobotMap::Climber::k_reverseMotorSpeed + tiltGain);
    Robot::m_climber->LowerExplicit(RobotMap::Climber::k_reverseMotorSpeed - tiltGain);
  }
  

}

// Make this return true when this Command no longer needs to run execute()
bool ClimbEvenly::IsFinished() { return false; }

// Called once after isFinished returns true
void ClimbEvenly::End() {
  //Should we put some hold voltage on the climber - 
  //  motors to help keep the robot still if the command is aborted?
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimbEvenly::Interrupted() {}
