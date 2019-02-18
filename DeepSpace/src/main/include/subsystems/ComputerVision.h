/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <cameraserver/CameraServer.h>
#include <frc/Servo.h>

#include <thread>
#include <map>
#include <atomic>

class ComputerVision : public frc::Subsystem {
 public:
  ComputerVision();

  enum class Target {
    Tape,
    Ball
  };

  void setTarget(Target objectToTarget);

  std::pair<double, double> getOffset();

 private:
  std::shared_ptr<cs::UsbCamera> m_camera;
  // std::shared_ptr<frc::Servo> m_servo;

  std::shared_ptr<std::thread> m_visionThread;

  std::atomic<Target> m_objectToTarget;
  std::atomic<double> m_horizontalOffset;
  std::atomic<double> m_verticalOffset;

  void m_visionTargetTapeSetup();
  std::pair<double, double> m_visionTargetTapeRun(cv::Mat frame);

  std::map<Target, void (*)()> m_visionTargetSetup;
  std::map<Target, std::pair<double, double> (*)(cv::Mat frame)> m_visionTargetRun;
};
