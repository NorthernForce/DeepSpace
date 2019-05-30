/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Timer.h>
#include <AHRS.h>

class IMU : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<AHRS> m_ahrs;
//  ahrs = new AHRS(SPI::Port::kMXP);
  double m_angleOffset = 0;
  double m_rotationOffset = 0;

 public:
  IMU();
  void InitDefaultCommand() override;
  void Periodic() override;
  float getAngle();
  void resetAngle();
  float getRotation();
  void resetRotation();
  bool hasCollided();

 private:

  double m_lastAccelX = 0.0;
  double m_lastAccelY = 0.0;

  const static double k_rumbleMultiplier;
  
  const static double k_maxJerkForCollision;
  const static double k_collisionPeriod;
  std::shared_ptr<frc::Timer> m_collisionTimer;
};
