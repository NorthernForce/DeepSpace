/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <AHRS.h>

class IMU : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<AHRS> m_ahrs;
//  ahrs = new AHRS(SPI::Port::kMXP);
  double m_angleOffset = 0;



 public:
  IMU();
  float getAngle();
  void resetAngle();
  void InitDefaultCommand() override;
};
