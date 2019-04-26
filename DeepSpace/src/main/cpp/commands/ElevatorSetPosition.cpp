/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorSetPosition.h"

#include <iostream>

// allows for differetn limit switches between robots - adjust accordingly
const int ElevatorSetPosition::k_limitSwitchOffset = -350;
// const double ElevatorSetPosition::k_calibrationSpeed = -0.4;

const std::map<ElevatorSetPosition::Position, int> ElevatorSetPosition::m_setpoints = {
		{ Position::HomePosition, 0 + k_limitSwitchOffset},
#ifdef COMPETITION_ROBOT
    { Position::CargoIntake, -320 + k_limitSwitchOffset},
    { Position::HatchPanelIntake, 450 + k_limitSwitchOffset},
    { Position::CargoDepositLevel1, 3400 + k_limitSwitchOffset},
    { Position::CargoDepositLevel2, 8000 + k_limitSwitchOffset},
    { Position::CargoDepositLevel3, 12426 + k_limitSwitchOffset},
    { Position::CargoShipCargoDeposit, 5859 + k_limitSwitchOffset},
    { Position::HatchDepositLevel1, 450 + k_limitSwitchOffset},
    { Position::HatchDepositLevel2, 5230 + k_limitSwitchOffset},
    { Position::HatchDepositLevel3, 9791 + k_limitSwitchOffset},
    { Position::ClimbPosition, 3355 + k_limitSwitchOffset},
#else
    { Position::CargoIntake, 215 + k_limitSwitchOffset},
    { Position::HatchPanelIntake, 664 + k_limitSwitchOffset},
    { Position::CargoDepositLevel1, 3188 + k_limitSwitchOffset},
    { Position::CargoDepositLevel2, 6837 + k_limitSwitchOffset},
    { Position::CargoDepositLevel3, 10326 + k_limitSwitchOffset},
    { Position::CargoShipCargoDeposit, 5201 + k_limitSwitchOffset},
    { Position::HatchDepositLevel1, 664 + k_limitSwitchOffset},
    { Position::HatchDepositLevel2, 4505 + k_limitSwitchOffset},
    { Position::HatchDepositLevel3, 8356 + k_limitSwitchOffset},
    { Position::ClimbPosition, 3188 + k_limitSwitchOffset},
#endif
};

ElevatorSetPosition::ElevatorSetPosition(Position pos) : Command("ElevatorSetPosition"),
  m_elevator(Robot::m_elevator.get())
{
	Requires(m_elevator.get());

  const auto setpointInMap = m_setpoints.find(pos);
  m_setpoint = setpointInMap->second;

  // if (m_setpoint == k_limitSwitchOffset) {
  //   m_calibrate = true;  
  // }
}

// Called just before this Command runs the first time
void ElevatorSetPosition::Initialize() {
  m_done = false;
  // m_timeToCalibrate = false;
  
  // if (m_calibrate) {
  //   Robot::m_elevator->enableReverseLimitSwitch();
  //   Robot::m_elevator->enableForwardLimitSwitch();
  // }
}

// Called repeatedly when this Command is scheduled to run
void ElevatorSetPosition::Execute() {
  // if (!m_timeToCalibrate) {
    m_elevator->setPosition(m_setpoint);

    if (m_elevator->atSetpoint()) {
      // if (m_calibrate) {
      //   m_timeToCalibrate = true;
      // }
      // else {
        m_done = true;
      // }
    }
  // }
  
  // if (m_timeToCalibrate) {
  //   if (m_elevator->atLowerLimit()) {
  //   //   m_elevator->setHomePosition();
  //     m_done = true;
  //   }
  //   else {
  //     m_elevator->setSpeed(k_calibrationSpeed);
  //   }
  // }
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSetPosition::IsFinished() { 
  return m_done;
}

// Called once after isFinished returns true
void ElevatorSetPosition::End() {
  // m_elevator->stop();

  // if (m_calibrate) {
  //   Robot::m_elevator->disableReverseLimitSwitch();
  //   Robot::m_elevator->disableForwardLimitSwitch();
  // }
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSetPosition::Interrupted() {
  m_elevator->stop();
}
