/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ComputerVision.h"

#include "RobotMap.h"

#include "subsystems/ComputerVisionTargets/TapeTarget.h"
#include "subsystems/ComputerVisionTargets/BallTarget.h"

ComputerVision::ComputerVision() : Subsystem("ComputerVision"),
  m_targets{
    std::make_shared<TapeTarget>(),
    std::make_shared<BallTarget>()
  } {
  // m_camera->SetResolution(640, 480);
  // m_sink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo("ComputerVision Camera"));

  // Set default target
  m_target = 0;

  m_visionThread.reset(new std::thread([&]{
    m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("ComputerVision Camera", RobotMap::ComputerVision::k_camera_id));
    m_sink = std::make_shared<cs::CvSink>(frc::CameraServer::GetInstance()->GetVideo("ComputerVision Camera"));
    m_debug = std::make_shared<cs::CvSource>(frc::CameraServer::GetInstance()->PutVideo("ComputerVision Debug", 160, 120));
    
    int currentTarget;

    for (;;) {
      if (currentTarget != m_target) {
        m_horizontalOffset = 0;
        m_verticalOffset = 0;

        currentTarget = m_target.load();

        // Reset all settings (v4l-utils)
        // TODODODODODOD

        // Call camera setup
        m_targets[currentTarget]->setup(m_camera);
      }

      cv::Mat frame;
      auto status = m_sink->GrabFrame(frame);
      std::cout << "status: " << status << "\n";
      if (status != 0) {
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
