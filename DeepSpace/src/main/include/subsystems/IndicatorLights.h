/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <frc/SPI.h>

class IndicatorLights : public frc::Subsystem {
 public:
  IndicatorLights();
  void InitDefaultCommand() override;

 private:
  std::shared_ptr<frc::SPI> m_spi;

  const static double k_hz;
};
