/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DigitalOutput.h>
#include <frc/AnalogInput.h>
#include <frc/PIDSource.h>

class RangeFinder : public frc::Subsystem, public frc::PIDSource
{
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  int m_lastRange; 
  std::shared_ptr<frc::DigitalOutput> m_ctrl;
  std::shared_ptr<frc::AnalogInput> m_voltageReader;
  double m_voltage;
  double m_rangeInches;
  frc::PIDSourceType m_pidSource;

 public:
  RangeFinder();
  void InitDefaultCommand() override;
  double getDistance();
  int enable();
  int disable();
  void SetPIDSourceType(frc::PIDSourceType pidSource) override;
  frc::PIDSourceType GetPIDSourceType() const override;
  double PIDGet() override;

  const static bool k_ultrasonicOn;
  const static bool k_ultrasonicOff;
};
