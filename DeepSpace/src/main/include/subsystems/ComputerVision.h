/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <cameraserver/CameraServer.h>

#include <thread>

class ComputerVision : public frc::Subsystem {
 private:
  std::shared_ptr<cs::UsbCamera> m_camera;
  std::shared_ptr<std::thread> m_visionThread;

  std::shared_ptr<std::atomic<bool>> m_objectSwitched;
  std::shared_ptr<std::atomic<std::pair<double, double>>> m_distanceFromCenter;

 public:
  ComputerVision();
};
