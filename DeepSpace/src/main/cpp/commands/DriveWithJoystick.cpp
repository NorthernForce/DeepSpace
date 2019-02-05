/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoystick.h"

#include "Robot.h"

DriveWithJoystick::DriveWithJoystick() {
	Requires(Robot::m_driveTrain.get());
}

// Called just before this Command runs the first time
void DriveWithJoystick::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystick::Execute() {
	const auto& driverController = Robot::m_oi->getDriverController();

	const double y = driverController->GetY(JoystickFunctions::k_forward);
	const double x = driverController->GetX(JoystickFunctions::k_turn);

	auto& driveTrain = Robot::m_driveTrain;
	driveTrain->arcDrive(y, x);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystick::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveWithJoystick::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystick::Interrupted() {}
