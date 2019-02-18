/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ComputerVision.h"

#include "RobotMap.h"

ComputerVision::ComputerVision() : Subsystem("ComputerVision") {
  m_camera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("Driver Camera", RobotMap::ComputerVision::k_camera_id));
  // m_servo.reset(new frc::Servo(RobotMap::ComputerVision::k_servo_id));

  m_visionTargetSetup[Target::Tape] = m_visionTargetTapeSetup;

  m_visionThread.reset(new std::thread([&]{
    // Set default target
    Target currentTarget = Target::Tape;

    for (;;) {
      if (currentTarget != m_objectToTarget) {
        currentTarget = m_objectToTarget.load();

        // call camera setup
      }

      //   Call enum to function map
      //      example function: std::pair<double, double> getTape(cs::Mat)

      if (currentTarget == m_objectToTarget) {
        // set atomics
      }
      else {
        m_horizontalOffset = 0;
        m_verticalOffset = 0;
      }
    }
  }));
}

void ComputerVision::setTarget(Target target) {
  m_objectToTarget = target;
}

std::pair<double, double> ComputerVision::getOffset() {
  return std::make_pair(m_horizontalOffset.load(), m_verticalOffset.load());
}