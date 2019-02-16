/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

#include <ctre/Phoenix.h>

#include "RobotMap.h"

Elevator::Elevator() : Subsystem("Elevator") { 
  
    m_primaryTalonElevator.reset(new WPI_TalonSRX (RobotMap::Elevator::k_primary_id));
    m_followerTalonElevator1.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower1_id));
    m_followerTalonElevator2.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower2_id));
    m_followerTalonElevator3.reset(new WPI_TalonSRX (RobotMap::Elevator::k_follower3_id));

    m_followerTalonElevator1->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator2->Follow(*m_primaryTalonElevator);
    m_followerTalonElevator3->Follow(*m_primaryTalonElevator);

}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void Elevator::Raise(){
   m_primaryTalonElevator->Set(RobotMap::Elevator::k_elevatorRaiseSpeed);

//Elevator has 3 floors
}
void Elevator::Lower(){
   m_primaryTalonElevator->Set(RobotMap::Elevator::k_elevatorLowerSpeed);

  //Elevator has 3 floors 
}
// Put methods for controlling this subsystem
// here. Call these from Commands