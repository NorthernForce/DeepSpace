#pragma once

#include "subsystems/Vision/Targets/Target.h"

#include <cameraserver/CameraServer.h>
#include <frc/Relay.h>

#include <string>
#include <chrono>
#include <thread>
#include <atomic>

namespace Vision {

class Target;

class Camera {
 public:
  Camera(std::string name, std::string devPath, int width = 160, int height = 120, int fps = 30, int lightRingID = -1);
  void process();
  void updateSettings(std::string newSettings);
  void setLightRing(bool turnOn);
  void setTarget(std::shared_ptr<Target> target);

  const static std::string k_defaultSettings;

 private:
  std::string m_name;
  std::string m_path;

  std::string m_baseCommand;

  std::shared_ptr<cs::UsbCamera> m_camera;
  std::shared_ptr<cs::CvSink> m_cameraSink;
  std::shared_ptr<cs::CvSource> m_debugStream;

  std::shared_ptr<frc::Relay> m_lightRing;

  std::shared_ptr<Target> m_objectToTarget;
  std::shared_ptr<Target> m_currentTarget;

  const static int k_cameraSettingsDelayMillis;
};

}