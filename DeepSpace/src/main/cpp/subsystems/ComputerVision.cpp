/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ComputerVision.h"

#include "subsystems/ComputerVisionTargets/TapeTarget.h"
#include "subsystems/ComputerVisionTargets/BallTarget.h"

#include "RobotMap.h"

const std::string ComputerVision::cameraSettingsBaseCommand = 
  "v4l2-ctl --device "
  + std::string(RobotMap::ComputerVision::k_camera_path)
  + " --set-ctrl ";

const std::string ComputerVision::cameraSettingsDefaultCommand = ComputerVision::cameraSettingsBaseCommand +
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

ComputerVision::ComputerVision() : Subsystem("ComputerVision"),
  m_targets{
    std::make_shared<TapeTarget>(),
    std::make_shared<BallTarget>()
  } {

  // Set default target
  m_target = 0;

  m_visionThread.reset(new std::thread([&]{
    m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("ComputerVision Camera", RobotMap::ComputerVision::k_camera_path));
    m_sink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo("ComputerVision Camera"));
    m_debug = std::make_shared<cs::CvSource>(frc::CameraServer::GetInstance()->PutVideo("ComputerVision Debug", 160, 120));
    
    int currentTarget;

    for (;;) {
      if (currentTarget != m_target) {
        m_horizontalOffset = 0;
        m_verticalOffset = 0;

        currentTarget = m_target.load();

        // Reset all settings (v4l-utils)
        system(ComputerVision::cameraSettingsDefaultCommand.c_str());

        // Call camera setup
        m_targets[currentTarget]->setup();
      }

      cv::Mat frame;
      auto status = m_sink->GrabFrame(frame);

      if (status == 0) {
        std::cout << "ComputerVision Error: " << m_sink->GetError() << "\n";
      }
      else {
        auto offsets = m_targets[currentTarget]->run(frame, m_debug);

        if (currentTarget == m_target) {
          m_horizontalOffset = offsets.first;
          m_verticalOffset = offsets.second;
        }
        else {
          m_horizontalOffset = 0;
          m_verticalOffset = 0;
        }
      }
    }
  }));
}

void ComputerVision::setTarget(std::string targetName) {
  auto pos = std::find_if(m_targets.begin(), m_targets.end(),
    [&targetName](const std::shared_ptr<Target>& testTarget) {
      return targetName.compare(testTarget->name);
    }
  );

  if (pos != m_targets.end()) {
    m_target = std::distance(m_targets.begin(), pos);

    // Just in case set the offsets to zero.
    m_horizontalOffset = 0;
    m_verticalOffset = 0;
  }
}

std::pair<double, double> ComputerVision::getOffset() {
  return std::make_pair(m_horizontalOffset.load(), m_verticalOffset.load());
}
