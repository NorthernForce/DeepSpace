/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IndicatorLights.h"

#include "RobotMap.h"

const int IndicatorLights::k_numberOfLeds = 1;

// 4 MHz -> Period of 0.25 us
const double IndicatorLights::k_hz = 4000000;

IndicatorLights::IndicatorLights() : Subsystem("IndicatorLights") {
  m_spi.reset(new frc::SPI(static_cast<frc::SPI::Port>(RobotMap::IndicatorLights::k_chipSelect_id)));
  m_rawBuffer = (uint8_t*)std::malloc(k_numberOfLeds * 12);

  // This way 1 on + 3 off = 0 and 2 on + 2 off = 1
  m_spi->SetClockRate(k_hz);
  // TODO: consider the algorithm
  m_spi->SetLSBFirst();
}

void IndicatorLights::InitDefaultCommand() {}

void IndicatorLights::assembleFrame(uint8_t *colors, int numberOfColors) {
  // Clear the buffer.

  for (int colorI = 0; colorI < numberOfColors; colorI++) {
    for (int channelI = 0; channelI < 3; channelI++) {
      for (int bitI = 0; bitI < 8; bitI++) {
        if (bitI % 2 == 0) {
          // m_rawBuffer[colorI * 12 + channelI * 4 + bitI];
        }
        else {

        }
      }
    }
  }
}