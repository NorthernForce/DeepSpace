/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "RobotMap.h"

#include <frc/shuffleboard/Shuffleboard.h>

#include "triggers/SimpleAxis.h"
#include "triggers/SimpleButton.h"
#include "triggers/ComboButton.h"

// Command inclusions
#include "commands/CargoIntake.h"
#include "commands/CargoEject.h"

#include "commands/ClawClose.h"
#include "commands/ClawOpen.h"
#include "commands/ClawToggleRaise.h"

#include "commands/ClimbStage1.h"
#include "commands/ClimbEvenlyUp.h"
#include "commands/ClimberDriveForward.h"
#include "commands/ClimberDriveStop.h"
#include "commands/ClimberLower.h"
#include "commands/ClimberRaise.h"

#include "commands/ElevatorLower.h"
#include "commands/ElevatorRaise.h"
#include "commands/ElevatorStop.h"
#include "commands/ElevatorSetup.h"
#include "commands/ElevatorCalibrate.h"
#include "commands/ElevatorToggleDeployment.h"
#include "commands/ElevatorSetPosition.h"

#include "commands/PlatformDrive.h"

#include "commands/SetupPosition.h"

#include "commands/VisionFollowReflectiveTape.h"
#include "commands/GotoTarget.h"

OI::OI() {
  // Initialize the controllers
  m_driverController.reset(new frc::XboxController(RobotMap::OI::k_driverController_id));
  m_manipulatorController1.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController1_id));
  m_manipulatorController2.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController2_id));
  m_manipulatorController3.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController3_id));

  // auto &basicCommandsTab = frc::Shuffleboard::GetTab("Basic Commands");
  // basicCommandsTab.Add("Cargo Intake", new CargoIntake());
  // basicCommandsTab.Add(new ElevatorCalibrate());

  // frc::ShuffleboardLayout& cargoLayout = basicCommandsTab.GetLayout("Cargo", "List Layout");
  // cargoLayout.Add("CargoIntake", new CargoIntake());
  // cargoLayout.Add("CargoEject", new CargoEject());
  // cargoLayout.Add("ElevatorRaise", new ElevatorRaise());
  // cargoLayout.Add("ElevatorLower", new ElevatorLower());

  SimpleButton(m_manipulatorController1, 1).WhileActive(new CargoIntake());
  SimpleButton(m_manipulatorController1, 1).WhenActive(new ClawClose());
  SimpleButton(m_manipulatorController1, 1).WhenInactive(new ClawOpen());

  SimpleButton(m_manipulatorController1, 3).WhileActive(new CargoEject());
  
  SimpleButton(m_manipulatorController1, 8).WhenActive(new ClawToggleRaise());

  SimpleButton(m_manipulatorController1, 7).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel1, SetupPosition::TargetType::Cargo));
  SimpleButton(m_manipulatorController1, 11).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel2, SetupPosition::TargetType::Cargo));
  SimpleButton(m_manipulatorController1, 10).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3, SetupPosition::TargetType::Cargo));
  
  SimpleButton(m_manipulatorController1, 4).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel1, SetupPosition::TargetType::Hatch));
  SimpleButton(m_manipulatorController1, 2).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel2, SetupPosition::TargetType::Hatch));
  SimpleButton(m_manipulatorController1, 5).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel3, SetupPosition::TargetType::Hatch));

  SimpleButton(m_manipulatorController1, 6).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoIntake, SetupPosition::TargetType::Cargo));
  SimpleButton(m_manipulatorController1, 9).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoShipCargoDeposit, SetupPosition::TargetType::Cargo));

  SimpleButton(m_manipulatorController2, 8).WhenActive(new ElevatorSetup());

  SimpleButton(m_manipulatorController2, 10).WhileActive(new ElevatorRaise());
  SimpleButton(m_manipulatorController2, 11).WhileActive(new ElevatorLower());

  SimpleButton(m_manipulatorController2, 10).WhenInactive(new ElevatorStop());
  SimpleButton(m_manipulatorController2, 11).WhenInactive(new ElevatorStop());

  SimpleButton(m_manipulatorController2, 4).WhenActive(new ElevatorToggleDeployment());
  SimpleButton(m_manipulatorController2, 5).WhenActive(new ElevatorCalibrate());

  SimpleButton(m_manipulatorController2, 6).WhileActive(new ClimberLower());
  SimpleButton(m_manipulatorController2, 7).WhileActive(new ClimberRaise());

  SimpleButton(m_manipulatorController2, 3).WhileActive(new ClimberDriveForward());

  SimpleButton(m_manipulatorController2, 2).WhileActive(new ClimbEvenlyUp());

  // SimpleButton(m_driverController, 5).WhileActive(new VisionFollowReflectiveTape());
  SimpleButton(m_driverController, 5).WhileActive(new GotoTarget());

  SimpleAxis(m_driverController, 3).WhileActive(new CargoIntake());
  SimpleAxis(m_driverController, 3).WhenActive(new ClawClose());
  SimpleAxis(m_driverController, 3).WhenInactive(new ClawOpen());

  SimpleAxis(m_driverController, 2).WhileActive(new CargoEject());
  
  ComboButton(m_manipulatorController2, 8, 9).WhenActive(new ClimberDriveForward());
  ComboButton(m_manipulatorController3, 6, 3).WhenActive(new ClimberDriveForward());

  ComboButton(m_manipulatorController3, 5, 1).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel1, SetupPosition::TargetType::Cargo));
  ComboButton(m_manipulatorController3, 5, 2).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel2, SetupPosition::TargetType::Cargo));
  ComboButton(m_manipulatorController3, 5, 4).WhenActive(new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3, SetupPosition::TargetType::Cargo));

  ComboButton(m_manipulatorController3, 6, 1).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel1, SetupPosition::TargetType::Hatch));
  ComboButton(m_manipulatorController3, 6, 2).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel2, SetupPosition::TargetType::Hatch));
  ComboButton(m_manipulatorController3, 6, 4).WhenActive(new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel3, SetupPosition::TargetType::Hatch));

  // SimpleButton(m_manipulatorController2, 6).WhenActive(new ClimbStage1());

  // m_driverController->SetRumble(frc::GenericHID::kLeftRumble, 1.0);
}

std::pair<double, double> OI::getSteeringControls() {
  double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
  double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);

  // if (m_driverController->GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand) < 0.5) {
  if (m_driverController->GetBumper(frc::XboxController::JoystickHand::kRightHand) == 1) {
    double rotationScaled = std::sqrt(std::abs(rotation) * 2 - std::pow(rotation, 2)) * 0.75;

    if (rotation > 0) {
      return std::make_pair(speed * 0.6, rotationScaled);
    }
    else {
      return std::make_pair(speed * 0.6, rotationScaled * -1);
    }
  }
  else {
    return std::make_pair(speed, rotation * 0.75);
  }
}
