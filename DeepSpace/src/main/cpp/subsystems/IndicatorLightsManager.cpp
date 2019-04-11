/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/IndicatorLightsManager.h"

#include "subsystems/IndicatorLights/Turning.h"
#include "subsystems/IndicatorLights/Morse.h"

#include "RobotMap.h"

const int IndicatorLights::Manager::k_maxLEDs = 6;
const int IndicatorLights::Manager::k_bytesPerChannel = 4;
const int IndicatorLights::Manager::k_channelsPerLED = 3;
const int IndicatorLights::Manager::k_bytesPerLED = k_channelsPerLED * k_bytesPerChannel;
const int IndicatorLights::Manager::k_bufferSize = k_maxLEDs * k_bytesPerLED;

/*
 * IMPORTANT: Color format is "BRG", NOT "RGB"
 */

// 4 MHz -> Period of 0.25 micro seconds
const double IndicatorLights::Manager::k_hz = 4000000;

const std::chrono::milliseconds IndicatorLights::Manager::k_framePeriod = std::chrono::milliseconds(35);

IndicatorLights::Manager::Manager() : Subsystem("IndicatorLights") {
  m_spi.reset(new frc::SPI(static_cast<frc::SPI::Port>(RobotMap::IndicatorLights::k_chipSelect_id)));
  m_buffer = (uint8_t*)std::malloc(k_bufferSize);

  // This way 1 on + 3 off = 0 and 2 on + 2 off = 1
  m_spi->SetClockRate(k_hz);

  m_spi->SetMSBFirst();

  // Set the default effect
  m_defaultEffect = std::make_shared<Turning>();
  setEffect();

  m_indicatorLightsThread.reset(new std::thread([&]{
    for (;;) {
      std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

      if (m_newEffect != m_currentEffect) {
        m_currentEffect = m_newEffect;

        if (m_currentEffect->isDone()) {
          m_currentEffect->reset();
        }
      }

      m_currentEffect->run();
      assembleFrame(m_currentEffect->getColors());
      sendFrame();

      if (m_currentEffect->isDone()) {
        m_currentEffect = nullptr;
        setEffect();
      }

      std::this_thread::sleep_until(startTime + k_framePeriod);
    }
  }));
}

void IndicatorLights::Manager::InitDefaultCommand() {}

void IndicatorLights::Manager::setEffect(std::shared_ptr<Effect> effect) {
  if (effect == nullptr) {
    effect = m_defaultEffect;
  }

  std::atomic_store(&m_newEffect, effect);
}

void IndicatorLights::Manager::assembleFrame(std::vector<std::vector<uint8_t>> colors) {
  auto numberOfColors = colors.size();
  if (numberOfColors > k_maxLEDs) {
    numberOfColors = k_maxLEDs;
  }

  // Clear the buffer.
  std::memset(m_buffer, 0, k_bufferSize);

  // Must have a color (will turn off LEDs)
  if (numberOfColors < 1) {
    return;
  }

  // Run through and assemble each bit
  for (int colorI = 0; colorI < numberOfColors; colorI++) {
    for (int channelI = 0; channelI < k_channelsPerLED; channelI++) {
      for (int bitI = 0; bitI < 8; bitI += 2) {
        int bytePos = colorI * k_bytesPerLED + channelI * k_bytesPerChannel + bitI / 2;

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

  // Copy the last LED value for any left over LEDs
  for (int copyI = numberOfColors; copyI < k_maxLEDs; copyI++) {
    std::memcpy(&m_buffer[copyI * k_bytesPerLED], &m_buffer[(numberOfColors - 1) * k_bytesPerLED], k_bytesPerLED);
  }

  // // Testing, set the whole buffer to a color to test logic
  // std::memset(m_buffer, 0b11001100, k_bufferSize);
}

void IndicatorLights::Manager::sendFrame() {
  m_spi->Write(m_buffer, k_bufferSize);
}