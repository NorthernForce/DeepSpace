/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

// #include <cameraserver/CameraServer.h>
// #include <frc/Servo.h>
// #include <frc/Relay.h>

// #include <opencv2/opencv.hpp>

#include "subsystems/Vision/Cameras/Camera.h"
#include "subsystems/Vision/Targets/Target.h"

#include "subsystems/IndicatorLights/Targetting.h"

#include <thread>
#include <map>
#include <string>

namespace Vision {

  class Manager : public frc::Subsystem {
  public:
    Manager();
    void setTarget(std::string cameraName, std::string targetName = "", bool enable = true);
    std::pair<double, double> getOffset(std::string targetName);
    void enableTargetting(std::string cameraName, bool enable = true);
    std::string getTarget(std::string cameraName);

  private:
    std::shared_ptr<std::thread> m_visionThread;

    std::map<std::string, std::shared_ptr<Vision::Target>> m_targets;
    std::map<std::string, std::shared_ptr<Vision::Camera>> m_cameras;

    std::shared_ptr<IndicatorLights::Targetting> m_indicatorLightsEffect = nullptr;
  };

}