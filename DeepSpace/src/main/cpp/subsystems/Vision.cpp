/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"

#include "subsystems/VisionTargets/TargetReflectiveTape.h"
#include "subsystems/VisionTargets/TargetCargo.h"

#include "RobotMap.h"

#include <frc/smartdashboard/SmartDashboard.h>

const std::string Vision::Camera::k_defaultSettings = 
  "brightness=133,"
  "contrast=5,"
  "saturation=83,"
  // "white_balance_temperature_auto=0," // Must be manual to change settings.
  // "white_balance_temperature=4500,"
  "white_balance_temperature_auto=1,"
  "power_line_frequency=2,"
  "sharpness=25,"
  "backlight_compensation=0,"
  "exposure_auto=1,"
  "exposure_absolute=156,"
  "pan_absolute=0,"
  "tilt_absolute=0,"
  "zoom_absolute=0";

const double Vision::Target::k_targetChangeDelay = 0.1;

Vision::Vision() : Subsystem("Vision"),
  m_cameras{
    {"Elevator", std::make_shared<Camera>("Elevator Camera", RobotMap::Vision::k_elevatorCamera_path, 240, 180, 30, RobotMap::Vision::k_elevatorCameraLightRing_id)},
    {"Manipulator", std::make_shared<Camera>("Manipulator Camera", RobotMap::Vision::k_manipulatorCamera_path)},
  },
  m_targets{
    {TargetReflectiveTape::k_name, std::make_shared<TargetReflectiveTape>()},
    {TargetCargo::k_name, std::make_shared<TargetCargo>()}
  } {

  // Default target
  // setTarget("Elevator", "ReflectiveTape");

  m_visionThread.reset(new std::thread([&]{
    for (;;) {
      for (const auto& camera : m_cameras) {
        camera.second->process();
      }
    }
  }));
}

void Vision::setTarget(std::string cameraName, std::string targetName) {
  if (targetName != "") {
    m_cameras[cameraName]->setTarget(m_targets[targetName]);
  }
  else {
    m_cameras[cameraName]->setTarget(nullptr);
  }
}

std::pair<double, double> Vision::getOffset(std::string targetName) {
  return m_targets[targetName]->getOffset();
}

Vision::Camera::Camera(std::string name, std::string devPath, int width, int height, int fps, int lightRingID) {
  m_name = name;
  m_path = devPath;

  m_baseCommand = "v4l2-ctl --device " +m_path +" --set-ctrl ";

  // This link has a way to get frames but not start automatic capture:
  // https://www.chiefdelphi.com/t/vision-processing-limits/339493/21
  // m_camera = std::make_shared<cs::UsbCamera>(m_name, m_path);
  // frc::GetCameraServerShared()->ReportUsbCamera(m_camera->GetHandle());
  m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture(m_name, m_path));
  m_camera->SetResolution(width, height);
  m_camera->SetFPS(fps);
  m_cameraSink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo(m_name));
  m_debugStream = std::make_shared<cs::CvSource>(frc::CameraServer::GetInstance()->PutVideo(m_name +" Debug", width, height));

  if (lightRingID != -1) {
    m_lightRing.reset(new frc::Relay(lightRingID, frc::Relay::kForwardOnly));
  }
}

void Vision::Camera::process() {
  if (m_currentTarget != m_objectToTarget) {
    if (m_currentTarget != nullptr) {
      m_currentTarget->resetOffset();
    }

    m_currentTarget = m_objectToTarget;

    // Reset all camera settings
    updateSettings(k_defaultSettings);
    setLightRing(false);

    // Call target setup
    if (m_currentTarget != nullptr) {
      m_currentTarget->setup(this);
    }
  }

  if (m_currentTarget != nullptr) {
    cv::Mat frame;
    auto status = m_cameraSink->GrabFrame(frame);

    if (status == 0) {
      std::cout << "Vision Error: " << m_name << ": " << m_cameraSink->GetError() << "\n";
    }
    else {
      m_currentTarget->run(frame);

      m_debugStream->PutFrame(frame);
    }
  }
}

void Vision::Camera::updateSettings(std::string newSettings) {
  system((m_baseCommand +newSettings).c_str());
}

void Vision::Camera::setLightRing(bool turnOn) {
  if (m_lightRing != nullptr) {
    if (turnOn) {
      m_lightRing->Set(frc::Relay::kOn);
    }
    else {
      m_lightRing->Set(frc::Relay::kOff);
    }
  }
}

void Vision::Camera::setTarget(std::shared_ptr<Target> target) {
  std::atomic_store(&m_objectToTarget, target);
}