/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Drive/DifferentialDrive.h>

// #include <rev/CANSparkMax.h>
#include "ctre/Phoenix.h"
#include "../include/RobotMap.h"

class WCDrive : public frc::Subsystem 
{
 public:
   WCDrive();
   
   void InitDefaultCommand(); //override;

   void arcDrive(int y, int x);
   

 private:

   WPI_TalonSRX        *m_leftWCDrive;
   WPI_TalonSRX        *m_rightWCDrive;
   frc::DifferentialDrive  *m_robotWCDrive;

   
};
