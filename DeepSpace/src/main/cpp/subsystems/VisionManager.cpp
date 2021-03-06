/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/VisionManager.h"

#include "subsystems/Vision/Targets/ReflectiveTape.h"
#include "subsystems/Vision/Targets/Cargo.h"

#include "Robot.h"
#include "RobotMap.h"

#include <frc/smartdashboard/SmartDashboard.h>

Vision::Manager::Manager() : Subsystem("VisionManager"),
  m_cameras{
    {"Targeter", std::make_shared<Vision::Camera>("Targeter Camera", RobotMap::Vision::k_targeterCamera_path, 240, 180, 30, true, RobotMap::Vision::k_targeterCameraLightRing_id)},
    {"Driver", std::make_shared<Vision::Camera>("Driver Camera", RobotMap::Vision::k_driverCamera_path, 240, 180, 30)},
  },
  m_targets{
    {"ReflectiveTape", std::make_shared<Vision::ReflectiveTape>()},
    {"Cargo", std::make_shared<Vision::Cargo>()}
  } {

  m_indicatorLightsEffect.reset(new IndicatorLights::Targetting());

  // Default target
  setTarget("Targeter", "ReflectiveTape", false);

  m_visionThread.reset(new std::thread([&]{
    for (;;) {
      for (const auto& camera : m_cameras) {
        camera.second->process();
      }
    }
  }));
}

void Vision::Manager::setTarget(std::string cameraName, std::string targetName, bool enable) {
  if (targetName != "") {
    m_cameras[cameraName]->setTarget(m_targets[targetName]);

    enableTargetting(cameraName, enable);
  }
  else {
    m_cameras[cameraName]->setTarget(nullptr);
    enableTargetting(cameraName, false);
  }
}

std::pair<double, double> Vision::Manager::getOffset(std::string targetName) {
  return m_targets[targetName]->getOffset();
}

std::string Vision::Manager::getTarget(std::string cameraName) {
  return m_cameras[cameraName]->getTarget();
}

void Vision::Manager::enableTargetting(std::string cameraName, bool enable) {
  m_cameras[cameraName]->enableTargetting(enable);

  if (enable && m_cameras[cameraName]->getTarget() != "") {
    Robot::m_indicatorLights->setEffect(m_indicatorLightsEffect);
  }
  else {
    Robot::m_indicatorLights->setEffect();
  }
}