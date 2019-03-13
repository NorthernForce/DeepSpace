/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <map>
#include "../Robot.h"

class ElevatorSetPosition : public frc::Command {
 public:

  enum class Position {
    HomePosition,
    CargoIntake,	
    HatchPanelIntake,		
    CargoDepositLevel1,	
    CargoDepositLevel2,	
    CargoDepositLevel3,
    CargoShipCargoDeposit,
    HatchDepositLevel1,
    HatchDepositLevel2,
    HatchDepositLevel3,
    ClimbPosition,
  };

  ElevatorSetPosition(Position position);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  static const std::map<Position, int> m_setpoints;

  const std::shared_ptr<Elevator> m_elevator;

  Position m_position;
};
