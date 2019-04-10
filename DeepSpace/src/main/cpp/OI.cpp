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
#include <frc/buttons/POVButton.h>

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

#include "commands/IndicatorLightsEffect.h"
#include "subsystems/IndicatorLights/Pulse.h"
#include "subsystems/IndicatorLights/Morse.h"
#include "subsystems/IndicatorLights/Turning.h"

// Functions to simplify button mapping.
static void WhenPressed(frc::Trigger* trigger, frc::Command* command) {
  trigger->WhenActive(command);
}
static void WhenReleased(frc::Trigger* trigger, frc::Command* command) {
  trigger->WhenInactive(command);
}
static void WhileHeld(frc::Trigger* trigger, frc::Command* command) {
  trigger->WhileActive(command);
}

OI::OI() {
  // Initialize the controllers
  m_driverController.reset(new frc::XboxController(RobotMap::OI::k_driverController_id));
  m_manipulatorController1.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController1_id));
  m_manipulatorController2.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController2_id));
  m_manipulatorController3.reset(new frc::XboxController(RobotMap::OI::k_manipulatorController3_id));

  // auto &basicCommandsTab = frc::Shuffleboard::GetTab("Basic Commands");
  // basicCommandsTab.Add("Cargo Intake", new CargoIntake());
  // basicCommandsTab.Add(new ElevatorCalibrate());

  // frc::ShuffleboardLayout& cargoLayout = basicCommandsTab.GetLayout("Cargo", "List Layout");
  // cargoLayout.Add("CargoIntake", new CargoIntake());
  // cargoLayout.Add("CargoEject", new CargoEject());
  // cargoLayout.Add("ElevatorRaise", new ElevatorRaise());
  // cargoLayout.Add("ElevatorLower", new ElevatorLower());

  WhileHeld(new SimpleButton(m_driverController, 5), new VisionFollowReflectiveTape());
  // WhileHeld(new SimpleButton(m_driverController, 5), new GotoTarget());
  
  WhileHeld(new SimpleButton(m_driverController, 1), new ClawToggleRaise());

  WhileHeld(new SimpleAxis(m_driverController, 3), new CargoIntake());
  WhenPressed(new SimpleAxis(m_driverController, 3), new ClawClose());
  WhenReleased(new SimpleAxis(m_driverController, 3), new ClawOpen());

  WhileHeld(new SimpleAxis(m_driverController, 2), new CargoEject());

  WhenPressed(new SimpleButton(m_driverController, 3), new IndicatorLightsEffect(std::make_shared<IndicatorLights::Pulse>(std::vector<uint8_t>{148, 248, 24}, 0.2)));
  WhenPressed(new SimpleButton(m_driverController, 9), new IndicatorLightsEffect(std::make_shared<IndicatorLights::Pulse>(std::vector<uint8_t>{148, 248, 24}, 0.2)));
  WhenPressed(new frc::POVButton(*m_driverController, 0), new IndicatorLightsEffect());
  WhenPressed(new frc::POVButton(*m_driverController, 90), new IndicatorLightsEffect(std::make_shared<IndicatorLights::Morse>("SOS")));
  WhenPressed(new frc::POVButton(*m_driverController, 180), new IndicatorLightsEffect(std::make_shared<IndicatorLights::Morse>("we will pillage your village", 20, std::vector<uint8_t>{255, 255, 0})));
  WhenPressed(new frc::POVButton(*m_driverController, 270), new IndicatorLightsEffect(std::make_shared<IndicatorLights::Morse>("go 172", 20, std::vector<uint8_t>{156, 254, 127})));

  // auto test = new SimpleButton(m_manipulatorController1, 1);
  // test->WhileActive(new CargoIntake());
  WhileHeld(new SimpleButton(m_manipulatorController1, 1), new CargoIntake());
  WhenPressed(new SimpleButton(m_manipulatorController1, 1), new ClawClose());
  WhenReleased(new SimpleButton(m_manipulatorController1, 1), new ClawOpen());

  WhileHeld(new SimpleButton(m_manipulatorController1, 3), new CargoEject());
  
  WhenPressed(new SimpleButton(m_manipulatorController1, 8), new ClawToggleRaise());

  WhenPressed(new SimpleButton(m_manipulatorController1, 7), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel1, SetupPosition::TargetType::Cargo));
  WhenPressed(new SimpleButton(m_manipulatorController1, 11), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel2, SetupPosition::TargetType::Cargo));
  WhenPressed(new SimpleButton(m_manipulatorController1, 10), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3, SetupPosition::TargetType::Cargo));
  
  WhenPressed(new SimpleButton(m_manipulatorController1, 4), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel1, SetupPosition::TargetType::Hatch));
  WhenPressed(new SimpleButton(m_manipulatorController1, 2), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel2, SetupPosition::TargetType::Hatch));
  WhenPressed(new SimpleButton(m_manipulatorController1, 5), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel3, SetupPosition::TargetType::Hatch));

  WhenPressed(new SimpleButton(m_manipulatorController1, 6), new SetupPosition(ElevatorSetPosition::Position::CargoIntake, SetupPosition::TargetType::Cargo));
  WhenPressed(new SimpleButton(m_manipulatorController1, 9), new SetupPosition(ElevatorSetPosition::Position::CargoShipCargoDeposit, SetupPosition::TargetType::Cargo));

  WhenPressed(new SimpleButton(m_manipulatorController2, 8), new ElevatorSetup());

  WhileHeld(new SimpleButton(m_manipulatorController2, 10), new ElevatorRaise());
  WhileHeld(new SimpleButton(m_manipulatorController2, 11), new ElevatorLower());

  WhenReleased(new SimpleButton(m_manipulatorController2, 10), new ElevatorStop());
  WhenReleased(new SimpleButton(m_manipulatorController2, 11), new ElevatorStop());

  WhenPressed(new SimpleButton(m_manipulatorController2, 4), new ElevatorToggleDeployment());
  WhenPressed(new SimpleButton(m_manipulatorController2, 5), new ElevatorCalibrate());

  WhileHeld(new SimpleButton(m_manipulatorController2, 6), new ClimberLower());
  WhileHeld(new SimpleButton(m_manipulatorController2, 7), new ClimberRaise());

  WhileHeld(new SimpleButton(m_manipulatorController2, 3), new ClimberDriveForward());

  WhileHeld(new SimpleButton(m_manipulatorController2, 2), new ClimbEvenlyUp());
  
  // WhenPressed(new ComboButton(m_manipulatorController2, 8, 9), new ClimberDriveForward());
  // WhenPressed(new ComboButton(m_manipulatorController3, 6, 3), new ClimberDriveForward());

  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 5), new SimpleButton(m_manipulatorController3, 1)), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel1, SetupPosition::TargetType::Cargo));
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 5), new SimpleButton(m_manipulatorController3, 2)), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel2, SetupPosition::TargetType::Cargo));
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 5), new SimpleButton(m_manipulatorController3, 4)), new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3, SetupPosition::TargetType::Cargo));

  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 6), new SimpleButton(m_manipulatorController3, 1)), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel1, SetupPosition::TargetType::Hatch));
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 6), new SimpleButton(m_manipulatorController3, 2)), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel2, SetupPosition::TargetType::Hatch));
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 6), new SimpleButton(m_manipulatorController3, 4)), new SetupPosition(ElevatorSetPosition::Position::HatchDepositLevel3, SetupPosition::TargetType::Hatch));

  WhenPressed(new SimpleButton(m_manipulatorController3, 8), new ElevatorCalibrate());
  WhenPressed(new SimpleButton(m_manipulatorController3, 7), new ElevatorToggleDeployment());

  WhenPressed(new frc::POVButton(*m_manipulatorController3, 270), new ClimbEvenlyUp());
  WhenPressed(new frc::POVButton(*m_manipulatorController3, 225), new ClimbEvenlyUp());
  WhileHeld(new frc::POVButton(*m_manipulatorController3, 225), new ClimberDriveForward());
  WhileHeld(new frc::POVButton(*m_manipulatorController3, 180), new ClimberDriveForward());

  WhenPressed(new frc::POVButton(*m_manipulatorController3, 0), new SetupPosition(ElevatorSetPosition::Position::ClimbPosition, SetupPosition::TargetType::Cargo));
  
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 5), new SimpleAxis(m_manipulatorController3, 2)), new SetupPosition(ElevatorSetPosition::Position::CargoIntake, SetupPosition::TargetType::Cargo));
  WhenPressed(new ComboButton(new SimpleButton(m_manipulatorController3, 5), new SimpleAxis(m_manipulatorController3, 3)), new SetupPosition(ElevatorSetPosition::Position::CargoShipCargoDeposit, SetupPosition::TargetType::Cargo));
  
  WhileHeld(new SimpleAxis(m_manipulatorController3, 1, -1, -0.5), new ElevatorRaise());
  WhileHeld(new SimpleAxis(m_manipulatorController3, 1, 0.5, 1), new ElevatorLower());
  
  WhileHeld(new SimpleAxis(m_manipulatorController3, 5, -1, -0.5), new ClimberRaise());
  WhileHeld(new SimpleAxis(m_manipulatorController3, 5, 0.5, 1), new ClimberLower());

  // SimpleButton(m_manipulatorController2, 6), new ClimbStage1());

  // m_driverController->SetRumble(frc::GenericHID::kLeftRumble, 1.0);
}

std::pair<double, double> OI::getSteeringControls() {
  double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
  double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);

  // if (m_driverController->GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand) < 0.5) {
  if (m_driverController->GetBumper(frc::XboxController::JoystickHand::kRightHand) == 1) {
    return std::make_pair(speed * 0.5, rotation * 0.3);
  }
  else {
    return std::make_pair(speed, rotation * 0.835);
  }
}

void OI::setControllerRumble(double value) {
  // m_driverController->SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
  m_driverController->SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
}