/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "RobotMap.h"

#include <frc/DigitalInput.h>

class LineTracker : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<frc::DigitalInput> m_lineSensorCenter;
  std::shared_ptr<frc::DigitalInput> m_lineSensorLeft;
  std::shared_ptr<frc::DigitalInput> m_lineSensorRight;

 public:
  LineTracker();
  void InitDefaultCommand() override;
  int getLineSensors();
};
