/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Relay.h>

class LightRing : public frc::Subsystem 
{
 private:
  std::shared_ptr<frc::Relay> m_Relay;

 public:
  LightRing();
  void InitDefaultCommand() override;
  void LightRingOn();
  void LightRingOff();
  
};
