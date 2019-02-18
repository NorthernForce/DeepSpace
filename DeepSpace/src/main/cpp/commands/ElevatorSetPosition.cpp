/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSetPosition.h"
#include <iostream>

const std::map<ElevatorSetPosition::Position, int> ElevatorSetPosition::m_setpoints = {
		{ ElevatorSetPosition::Position::HomePosition, 0 },
    { ElevatorSetPosition::Position::CargoIntake, 0 },
    { ElevatorSetPosition::Position::HatchPanelIntake, 3260 },
    { ElevatorSetPosition::Position::CargoDepositLevel1, 4718 },
    { ElevatorSetPosition::Position::CargoDepositLevel2, 9521 },
    { ElevatorSetPosition::Position::CargoDepositLevel3, 10325 },
    { ElevatorSetPosition::Position::HatchDepositLevel1, 3260 },
    { ElevatorSetPosition::Position::HatchDepositLevel2, 8063 },
    { ElevatorSetPosition::Position::HatchDepostiLevel3, 10866 }
};

ElevatorSetPosition::ElevatorSetPosition(Position pos) :
  m_elevator(Robot::m_elevator.get())
{
  
  std::cout << "Created elevator set position with position " << std::endl;
  m_position = pos;
	Requires(m_elevator.get());
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ElevatorSetPosition::Initialize() {
  
  std::cout << "Initalizing set position" << std::endl;
   const auto setpoint = m_setpoints.find(m_position);
  
  std::cout << "found setpoint " << std::endl;
	if (setpoint != m_setpoints.end()) {
  std::cout << "setting position to " << setpoint->second  << std::endl;
		m_elevator->SetPosition(setpoint->second);
	}
}

// Called repeatedly when this Command is scheduled to run
void ElevatorSetPosition::Execute() {
  
  std::cout << "ElevatorSetPosition executing " << std::endl;
  const bool elevatorDone = m_elevator->AtSetpoint();
  std::cout << "ElevatorSetPosition done executing " << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSetPosition::IsFinished() { 
  
  std::cout << "Set Position checking to see if finished" << std::endl;
  const bool elevatorDone = m_elevator->AtSetpoint();
  
  std::cout << "Set Poistion finished? " << elevatorDone << std::endl;
	return elevatorDone;
}

// Called once after isFinished returns true
void ElevatorSetPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSetPosition::Interrupted() {}
