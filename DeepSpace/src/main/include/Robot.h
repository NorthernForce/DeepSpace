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
#include "AHRS.h"

#include "OI.h"

#include "subsystems/BrushlessDrive.h"
#include "subsystems/Elevator.h"
#include "subsystems/CargoManipulator.h"
#include "subsystems/Claw.h"
#include "subsystems/LineTracker.h"
#include "subsystems/Climber.h"
#include "subsystems/ClimberDrive.h"
#include "subsystems/Claw.h"
#include "subsystems/IMU.h"
#include "subsystems/Vision.h"
#include "subsystems/RangeFinder.h"

class Robot : public frc::TimedRobot {
 public:
  static std::shared_ptr<OI> m_oi;

  static std::shared_ptr<BrushlessDrive> m_driveTrain;
  static std::shared_ptr<Elevator> m_elevator;
  static std::shared_ptr<CargoManipulator> m_cargoManipulator;
  static std::shared_ptr<Claw> m_claw;
  static std::shared_ptr<IMU> m_imu;
  static std::shared_ptr<LineTracker> m_lineTracker;
  static std::shared_ptr<Climber> m_climber;
  static std::shared_ptr<ClimberDrive> m_climberDrive;
  static std::shared_ptr<Vision> m_vision;
  static std::shared_ptr<RangeFinder> m_rangeFinder;

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
