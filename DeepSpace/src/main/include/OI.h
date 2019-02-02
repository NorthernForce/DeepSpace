/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/XboxController.h>

#include "RobotMap.h"

const auto kForward = frc::XboxController::JoystickHand::kLeftHand;
const auto kTurn = frc::XboxController::JoystickHand::kRightHand;

enum class JoystickFunctions {
  kForward = frc::XboxController::JoystickHand::kLeftHand,
  kTurn = frc::XboxController::JoystickHand::kRightHand,
  kElevatorUp,
  kElevatorDown
};

class OI {
 public:
  OI();
  const auto& getSteeringController() const {
    return m_driverController;
  }

 private:
  std::shared_ptr<frc::XboxController> m_driverController;
};
