/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "subsystems/BrushlessDrive.h"
<<<<<<< HEAD
#include "subsystems/Elevator.h"
=======
#include "subsystems/CargoManipulator.h"
>>>>>>> c9ca3308cf3ea480ad77de3e08902ead5d55240c
#include "subsystems/Claw.h"

class Robot : public frc::TimedRobot {
 public:
  static std::shared_ptr<OI> m_oi;

  static std::shared_ptr<BrushlessDrive> m_driveTrain;
<<<<<<< HEAD
  static std::shared_ptr<Elevator> m_elevator;
  //static std::shared_ptr<Claw> m_claw;
=======
  static std::shared_ptr<CargoManipulator> m_cargoManipulator;
  static std::shared_ptr<Claw> m_claw;
>>>>>>> c9ca3308cf3ea480ad77de3e08902ead5d55240c

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
};
