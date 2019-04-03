/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <frc/SPI.h>

#include "subsystems/IndicatorLights/Effect.h"

#include <vector>

namespace IndicatorLights {

class Manager : public frc::Subsystem {
 public:
  Manager();
  void InitDefaultCommand() override;
  void Periodic() override;
  void setEffect(std::shared_ptr<IndicatorLights::Effect> effect);

 private:
  void assembleFrame(std::vector<std::vector<uint8_t>> colors);
  void sendFrame();

  std::shared_ptr<frc::SPI> m_spi;
  uint8_t *m_buffer;

  std::shared_ptr<IndicatorLights::Effect> m_effect;

  const static int k_maxLEDs;
  const static int k_bytesPerChannel;
  const static int k_channelsPerLED;
  const static int k_bytesPerLED;
  const static int k_bufferSize;

  const static double k_hz;
};

}