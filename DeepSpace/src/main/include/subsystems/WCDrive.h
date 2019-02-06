/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Drive/DifferentialDrive.h>
#include "ctre/Phoenix.h"

class WCDrive : public frc::Subsystem 
{
 public:
   WCDrive();

   void InitDefaultCommand() override;

   void arcDrive(double speed, double rotation);
   
 private:
   std::shared_ptr<WPI_TalonSRX>        m_leftPrimaryTalon;
   std::shared_ptr<WPI_TalonSRX>        m_rightPrimaryTalon;

   std::shared_ptr<frc::DifferentialDrive>  m_robotWCDrive;
};
