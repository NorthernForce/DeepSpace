/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Vision.h"

#include "subsystems/VisionTargets/TapeTarget.h"
#include "subsystems/VisionTargets/BallTarget.h"

#include "RobotMap.h"

const std::string Vision::Camera::defaultSettings =
  "brightness=133,"
  "contrast=5,"
  "saturation=83,"
  "white_balance_temperature_auto=1,"
  "power_line_frequency=2,"
  "white_balance_temperature=4500,"
  "sharpness=25,"
  "backlight_compensation=0,"
  "exposure_auto=1,"
  "exposure_absolute=156,"
  "pan_absolute=0,"
  "tilt_absolute=0,"
  "zoom_absolute=0";

Vision::Vision() : Subsystem("Vision"),
  m_cameras{
    {"Elevator", std::make_shared<Camera>("Elevator Camera", RobotMap::Vision::k_elevatorCamera_path)},
    {"Manipulator", std::make_shared<Camera>("Manipulator Camera", RobotMap::Vision::k_manipulatorCamera_path)},
  },
  m_targets{
    {"Tape", std::make_shared<TapeTarget>()},
    {"Ball", std::make_shared<BallTarget>()}
  } {

  // Default target
  setTarget("Elevator", "Tape");

  m_visionThread.reset(new std::thread([&]{
    for (;;) {
      for (const auto& camera : m_cameras) {
      // for (const auto& [name, camera] : m_cameras) {
        camera.second->process();
      }
    }
  }));
}

void Vision::setTarget(std::string cameraName, std::string targetName) {
  m_cameras[cameraName]->setTarget(m_targets[targetName]);
}

std::pair<double, double> Vision::getOffset(std::string targetName) {
  return m_targets[targetName]->getOffset();
}

Vision::Camera::Camera(std::string name, std::string devPath) {
  m_name = name;
  m_path = devPath;

  m_baseCommand = "v4l2-ctl --device " +m_path +" --set-ctrl ";

  // m_camera = std::make_shared<cs::UsbCamera>(m_name, m_path);
  // frc::GetCameraServerShared()->ReportUsbCamera(m_camera->GetHandle());
  m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture(m_name, m_path));
  m_sink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo(m_name));
  m_source = std::make_shared<cs::CvSource>(frc::CameraServer::GetInstance()->PutVideo(m_name +" Result", 160, 120));
}

void Vision::Camera::process() {
  if (m_currentTarget->name != m_objectToTarget->name) {
    if (m_currentTarget != nullptr) {
      m_currentTarget->resetOffset();
    }

    m_currentTarget = m_objectToTarget;

    // Reset all camera settings
    updateSettings(defaultSettings);
    setLightring(false);

    // Call target setup
    m_currentTarget->setup(this);
  }

  cv::Mat frame;
  auto status = m_sink->GrabFrame(frame);

  if (status == 0) {
    std::cout << "Vision Error: " << m_name << ": " << m_sink->GetError() << "\n";
  }
  else {
    if (m_currentTarget != nullptr) {
      m_currentTarget->run(frame);
    }

    m_source->PutFrame(frame);
  }
}

void Vision::Camera::updateSettings(std::string newSettings) {
  system((m_baseCommand +newSettings).c_str());
}

void Vision::Camera::setLightring(bool turnOn) {
  // Check if defined
}

void Vision::Camera::setTarget(std::shared_ptr<Target> target) {
  std::atomic_store(&m_objectToTarget, target);
}