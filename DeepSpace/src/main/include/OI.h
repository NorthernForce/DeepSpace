/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/XboxController.h>
#include <frc/Joystick.h>

const static int k_driverController_id = 0;
const static int k_manipulatorController_id = 1;

namespace JoystickFunctions {
  const static auto k_forward = frc::XboxController::JoystickHand::kLeftHand;
  const static auto k_turn = frc::XboxController::JoystickHand::kRightHand;
  // const static int k_elevatorUp;
  // const static int k_elevatorDown;
}

class OI {
 public:
  OI();
  
  const auto& getDriverController() {
    return m_driverController;
  }

  const auto& getManipulatorController() {
    return m_manipulatorController;
  }

 private:
  std::shared_ptr<frc::XboxController> m_driverController;
  std::shared_ptr<frc::Joystick> m_manipulatorController;
};
