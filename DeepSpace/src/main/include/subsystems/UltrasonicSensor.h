/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <RobotMap.h>

#include <frc/Ultrasonic.h>

class UltrasonicSensor : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<frc::Ultrasonic> m_ultrasonicSensor;

 public:
  UltrasonicSensor();
  int GetDistanceToWall();
  void InitDefaultCommand() override;
};
