/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ComputerVision.h"

#include "RobotMap.h"

ComputerVision::ComputerVision() : Subsystem("ComputerVision") {
  m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("Driver Camera", RobotMap::ComputerVision::k_camera_id));

  m_visionThread.reset(new std::thread());
}
