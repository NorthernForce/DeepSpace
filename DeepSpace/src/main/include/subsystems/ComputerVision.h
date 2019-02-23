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

#include <opencv2/opencv.hpp>

#include <thread>
#include <vector>
#include <atomic>
#include <string>

class ComputerVision : public frc::Subsystem {
 public:
  ComputerVision();

  class Target {
    public:
      virtual void setup() = 0;
      virtual std::pair<double, double> run(cv::Mat frame, std::shared_ptr<cs::CvSource> debug) = 0;
      const std::string name = "";
    
    private:
  };

  void setTarget(std::string objectToTarget);

  std::pair<double, double> getOffset();

  static const std::string cameraSettingsBaseCommand;
  static const std::string cameraSettingsDefaultCommand;

 private:
  std::shared_ptr<cs::UsbCamera> m_camera;
  std::shared_ptr<cs::CvSink> m_sink;
  std::shared_ptr<cs::CvSource> m_debug;

  std::shared_ptr<std::thread> m_visionThread;

  std::atomic<int> m_target;
  std::atomic<double> m_horizontalOffset;
  std::atomic<double> m_verticalOffset;

  const std::vector<std::shared_ptr<Target>> m_targets;
};
