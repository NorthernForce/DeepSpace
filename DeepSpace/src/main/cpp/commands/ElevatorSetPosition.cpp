/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSetPosition.h"

#include <iostream>

// allows for differetn limit switches between robots - adjust accordingly
const int limitSwitchOffset = 0;

const std::map<ElevatorSetPosition::Position, int> ElevatorSetPosition::m_setpoints = {
		{ ElevatorSetPosition::Position::HomePosition, 0 + limitSwitchOffset},
    { ElevatorSetPosition::Position::CargoIntake, 367 + limitSwitchOffset},
    { ElevatorSetPosition::Position::HatchPanelIntake, 828 + limitSwitchOffset},
    { ElevatorSetPosition::Position::CargoDepositLevel1, 3838 + limitSwitchOffset},
    { ElevatorSetPosition::Position::CargoDepositLevel2, 8438 + limitSwitchOffset},
    { ElevatorSetPosition::Position::CargoDepositLevel3, 12830 + limitSwitchOffset},
    { ElevatorSetPosition::Position::HatchDepositLevel1, 828 + limitSwitchOffset},
    { ElevatorSetPosition::Position::HatchDepositLevel2, 5500 + limitSwitchOffset},
    { ElevatorSetPosition::Position::HatchDepositLevel3, 10090 + limitSwitchOffset},
};

ElevatorSetPosition::ElevatorSetPosition(Position pos) :
  m_elevator(Robot::m_elevator.get())
{
  // std::cout << "Created elevator set position with position " << (int)pos << "\n";
  m_position = pos;
	Requires(m_elevator.get());
}

// Called just before this Command runs the first time
void ElevatorSetPosition::Initialize() {
  
  // std::cout << "Initalizing set position" << "\n";
   const auto setpoint = m_setpoints.find(m_position);
  
  // std::cout << "found setpoint " << "\n";
	if (setpoint != m_setpoints.end()) {
  // std::cout << "setting position to " << setpoint->second  << "\n";
		m_elevator->setPosition(setpoint->second);
	}
}

// Called repeatedly when this Command is scheduled to run
void ElevatorSetPosition::Execute() {
  
   const auto setpoint = m_setpoints.find(m_position);
  // std::cout << "ElevatorSetPosition executing " << "\n";
  m_elevator->setPosition(setpoint->second);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSetPosition::IsFinished() { 
  
  return m_elevator->atSetpoint();
  
}

// Called once after isFinished returns true
void ElevatorSetPosition::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSetPosition::Interrupted() {
  m_elevator->stop();
}
