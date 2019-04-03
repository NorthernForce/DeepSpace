/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <frc/SPI.h>

#include <vector>

class IndicatorLights : public frc::Subsystem {
 public:
  IndicatorLights();
  void InitDefaultCommand() override;
  void assembleFrame(std::vector<std::vector<uint8_t>> colors);
  void sendFrame();

 private:
  std::shared_ptr<frc::SPI> m_spi;
  uint8_t *m_buffer;

  const static int k_maxLEDs;
  const static int k_bufferSize;

  const static double k_hz;
};
