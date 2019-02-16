/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSetPosition.h"

const std::map<ElevatorSetPosition::Position, int> ElevatorSetPosition::m_setpoints = {
		{ ElevatorSetPosition::Position::HomePosition, 0 },
    { ElevatorSetPosition::Position::CargoIntake, 0 },
    { ElevatorSetPosition::Position::HatchPanelIntake, 3260 },
    { ElevatorSetPosition::Position::CargoDepositLevel1, 4718 },
    { ElevatorSetPosition::Position::CargoDepositLevel2, 9521 },
    { ElevatorSetPosition::Position::CargoDepositLevel3, 14325 },
    { ElevatorSetPosition::Position::HatchDepositLevel1, 3260 },
    { ElevatorSetPosition::Position::HatchDepositLevel2, 8063 },
    { ElevatorSetPosition::Position::HatchDepostiLevel3, 12866 }
};

ElevatorSetPosition::ElevatorSetPosition(Position pos) :
  m_elevator(Robot::m_elevator.get())
{
  m_position = pos;
	Requires(m_elevator.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ElevatorSetPosition::Initialize() {
   const auto setpoint = m_setpoints.find(m_position);
	if (setpoint != m_setpoints.end()) {
		m_elevator->SetPosition(setpoint->second);
	}
}

// Called repeatedly when this Command is scheduled to run
void ElevatorSetPosition::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSetPosition::IsFinished() { 
  const bool elevatorDone = m_elevator->AtSetpoint();
	return elevatorDone;
}

// Called once after isFinished returns true
void ElevatorSetPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSetPosition::Interrupted() {}
