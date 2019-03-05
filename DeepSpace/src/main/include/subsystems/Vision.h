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
#include <frc/Relay.h>

#include <opencv2/opencv.hpp>

#include <thread>
#include <map>
#include <atomic>
#include <string>

class Vision : public frc::Subsystem {
 public:
  Vision();
  void setTarget(std::string cameraName, std::string targetName = "");
  std::pair<double, double> getOffset(std::string targetName);

  class Camera;
  class Target;

  class Camera {
   public:
    Camera(std::string name, std::string devPath, int lightRingID = -1);
    void process();
    void updateSettings(std::string newSettings);
    void setLightRing(bool turnOn);
    void setTarget(std::shared_ptr<Target> target);

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

    const std::string k_defaultSettings = 
      "brightness=133,"
      "contrast=5,"
      "saturation=83,"
      // "white_balance_temperature_auto=0," // Must be manual to change settings.
      // "white_balance_temperature=4500,"
      // "white_balance_temperature_auto=1,"
      "power_line_frequency=2,"
      "sharpness=25,"
      "backlight_compensation=0,"
      "exposure_auto=1,"
      "exposure_absolute=156,"
      "pan_absolute=0,"
      "tilt_absolute=0,"
      "zoom_absolute=0";

    const int k_defaultFPS = 20;
    const int k_defaultWidth = 160;
    const int k_defaultHeight = 120;
  };

  class Target {
   public:
    virtual void setup(Vision::Camera *camera) = 0;
    virtual void run(cv::Mat &frame) = 0;
    const std::string name = "";

    void resetOffset() {
      m_horizontalOffset = 0;
      m_verticalOffset = 0;
    }

    std::pair<double, double> getOffset() {
      return std::make_pair(m_horizontalOffset.load(), m_verticalOffset.load());
    }

   protected:
    std::atomic<double> m_horizontalOffset;
    std::atomic<double> m_verticalOffset;
  };

 private:
  std::shared_ptr<std::thread> m_visionThread;

  std::map<std::string, std::shared_ptr<Target>> m_targets;
  std::map<std::string, std::shared_ptr<Camera>> m_cameras;
};
