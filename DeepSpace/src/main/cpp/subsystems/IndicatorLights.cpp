/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IndicatorLights.h"

#include "RobotMap.h"

const int IndicatorLights::k_maxLEDs = 6;
const int IndicatorLights::k_bufferSize = k_maxLEDs * 12;

// 4 MHz -> Period of 0.25 micro seconds
const double IndicatorLights::k_hz = 4000000;

IndicatorLights::IndicatorLights() : Subsystem("IndicatorLights") {
  m_spi.reset(new frc::SPI(static_cast<frc::SPI::Port>(RobotMap::IndicatorLights::k_chipSelect_id)));
  m_buffer = (uint8_t*)std::malloc(k_bufferSize);

  // This way 1 on + 3 off = 0 and 2 on + 2 off = 1
  m_spi->SetClockRate(k_hz);
  // TODO: consider the algorithm
  m_spi->SetMSBFirst();
}

void IndicatorLights::InitDefaultCommand() {}

void IndicatorLights::assembleFrame(std::vector<std::vector<uint8_t>> colors) {
  auto numberOfColors = colors.size();
  if (numberOfColors > k_maxLEDs) {
    numberOfColors = k_maxLEDs;
  }

  // Clear the buffer.
  std::memset(m_buffer, 0, k_bufferSize);

  for (int colorI = 0; colorI < numberOfColors; colorI++) {
    for (int channelI = 0; channelI < 3; channelI++) {
      for (int bitI = 0; bitI < 8; bitI += 2) {
        int bytePos = colorI * 12 + channelI * 4 + bitI / 2;

        if ((0b10000000 >> bitI) & colors[colorI][channelI]) {
          m_buffer[bytePos] |= 0b11000000;
        }
        else {
          m_buffer[bytePos] |= 0b10000000;
        }

        if ((0b10000000 >> (bitI + 1)) & colors[colorI][channelI]) {
          m_buffer[bytePos] |= 0b00001100;
        }
        else {
          m_buffer[bytePos] |= 0b00001000;
        }
      }
    }
  }

  // // Testing, set the whole buffer to a color to test logic
  // std::memset(m_buffer, 0b11001100, k_bufferSize);
}

void IndicatorLights::sendFrame() {
  m_spi->Write(m_buffer, k_bufferSize);
}