/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include "RobotMap.h"

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/buttons/JoystickButton.h>
#include <frc/buttons/Button.h>

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

#include "commands/PositionSetups/SetupForCargoDepositLevel1.h"
#include "commands/PositionSetups/SetupForCargoDepositLevel2.h"
#include "commands/PositionSetups/SetupForCargoDepositLevel3.h"
#include "commands/PositionSetups/SetupForCargoShipCargoDeposit.h"
#include "commands/PositionSetups/SetupForCargoIntake.h"
#include "commands/PositionSetups/SetupForHatchDepositLevel1.h"
#include "commands/PositionSetups/SetupForHatchDepositLevel2.h"
#include "commands/PositionSetups/SetupForHatchDepositLevel3.h"
#include "commands/SetupPosition.h"

#include "commands/VisionFollowReflectiveTape.h"

class SimpleAxis : public Button {
 public:
  SimpleAxis(GenericHID* joystick, int axisNumber, int threshold = 0.5) 
    : m_joystick(joystick), m_axisNumber(axisNumber) {}

  virtual ~SimpleAxis() = default;

  SimpleAxis(SimpleAxis&&) = default;
  SimpleAxis& operator=(SimpleAxis&&) = default;

  virtual bool Get() {
    return (m_joystick->GetRawAxis(m_axisNumber) > m_threshold);
  };

 private:
  GenericHID* m_joystick;
  int m_axisNumber;
  double m_threshold;
};

// Functions to simplify button mapping.
static void WhenPressed(std::shared_ptr<frc::GenericHID> joystick, int button, frc::Command* command) {
  auto joystickButton = new frc::JoystickButton(joystick.get(), button);
  joystickButton->WhenPressed(command);
}
static void WhenReleased(std::shared_ptr<frc::GenericHID> joystick, int button, frc::Command* command) {
  auto joystickButton = new frc::JoystickButton(joystick.get(), button);
  joystickButton->WhenReleased(command);
}
static void WhileHeld(std::shared_ptr<frc::GenericHID> joystick, int button, frc::Command* command) {
  auto joystickButton = new frc::JoystickButton(joystick.get(), button);
  joystickButton->WhileHeld(command);
}

static void WhenAxisPressed(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, frc::Command* command) {
  auto axis = new SimpleAxis(joystick.get(), axisNumber);
  axis->WhenPressed(command);
}
static void WhenAxisReleased(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, frc::Command* command) {
  auto axis = new SimpleAxis(joystick.get(), axisNumber);
  axis->WhenReleased(command);
}
static void WhileAxisHeld(std::shared_ptr<frc::GenericHID> joystick, int axisNumber, frc::Command* command) {
  auto axis = new SimpleAxis(joystick.get(), axisNumber);
  axis->WhileHeld(command);
}

OI::OI() {
  // Initialize the controllers
  m_driverController.reset(new frc::XboxController(RobotMap::OI::k_driverController_id));
  m_manipulatorController1.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController1_id));
  m_manipulatorController2.reset(new frc::Joystick(RobotMap::OI::k_manipulatorController2_id));

  // frc::ShuffleboardTab& basicCommandsTab = frc::Shuffleboard::GetTab("Basic Commands");
  // basicCommandsTab.Add("ElevatorSetup", new ElevatorSetup());
  // basicCommandsTab.Add("Calibrate Robot", new ElevatorCalibrate());

  // frc::ShuffleboardLayout& cargoLayout = basicCommandsTab.GetLayout("Cargo", "List Layout");
  // cargoLayout.Add("CargoIntake", new CargoIntake());
  // cargoLayout.Add("CargoEject", new CargoEject());
  // cargoLayout.Add("ElevatorRaise", new ElevatorRaise());
  // cargoLayout.Add("ElevatorLower", new ElevatorLower());

  WhileHeld(m_manipulatorController1, 1, new CargoIntake());
  WhenPressed(m_manipulatorController1, 1, new ClawClose());
  WhenReleased(m_manipulatorController1, 1, new ClawOpen());

  WhileHeld(m_manipulatorController1, 3, new CargoEject());
  
  WhenPressed(m_manipulatorController1, 8, new ClawToggleRaise());

  WhenPressed(m_manipulatorController1, 7, new SetupForCargoDepositLevel1());
  WhenPressed(m_manipulatorController1, 11, new SetupForCargoDepositLevel2());
  WhenPressed(m_manipulatorController1, 10, new SetupForCargoDepositLevel3());
  // WhenPressed(m_manipulatorController1, 7, new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel1,
  //                                                            SetupPosition::TargetType::Cargo));
  // WhenPressed(m_manipulatorController1, 11, new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel2,
  //                                                            SetupPosition::TargetType::Cargo));
  // WhenPressed(m_manipulatorController1, 10, new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3,
  //                                                            SetupPosition::TargetType::Cargo));
  
  WhenPressed(m_manipulatorController1, 4, new SetupForHatchDepositLevel1());
  WhenPressed(m_manipulatorController1, 2, new SetupForHatchDepositLevel2());
  WhenPressed(m_manipulatorController1, 5, new SetupForCargoShipCargoDeposit());
  // WhenPressed(m_manipulatorController1, 4, new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3,
  //                                                            SetupPosition::TargetType::Hatch));
  // WhenPressed(m_manipulatorController1, 2, new SetupPosition(ElevatorSetPosition::Position::CargoDepositLevel3,
  //                                                            SetupPosition::TargetType::Hatch));
  // WhenPressed(m_manipulatorController1, 5, new SetupPosition(ElevatorSetPosition::Position::CargoShipCargoDeposit,
  //                                                            SetupPosition::TargetType::Cargo));

  WhenPressed(m_manipulatorController1, 9, new ElevatorSetPosition(ElevatorSetPosition::Position::HomePosition));
  WhenPressed(m_manipulatorController1, 6, new SetupForCargoIntake());
  // WhenPressed(m_manipulatorController1, 6, new SetupPosition(ElevatorSetPosition::Position::CargoIntake,
                                                            //  SetupPosition::TargetType::Cargo));

  WhenPressed(m_manipulatorController2, 8, new ElevatorSetup());

  WhileHeld(m_manipulatorController2, 10, new ElevatorRaise());
  WhileHeld(m_manipulatorController2, 11, new ElevatorLower());

  WhenReleased(m_manipulatorController2, 10, new ElevatorStop());
  WhenReleased(m_manipulatorController2, 11, new ElevatorStop());

  WhenPressed(m_manipulatorController2, 4, new ElevatorToggleDeployment());
  WhenPressed(m_manipulatorController2, 5, new ElevatorCalibrate());

  WhileHeld(m_manipulatorController2, 6, new ClimberLower());
  WhileHeld(m_manipulatorController2, 7, new ClimberRaise());

  WhileHeld(m_manipulatorController2, 3, new ClimberDriveForward());

  WhileHeld(m_manipulatorController2, 2, new ClimbEvenlyUp());

  WhileHeld(m_driverController, 5, new VisionFollowReflectiveTape());

  WhileAxisHeld(m_driverController, 3, new CargoIntake());
  WhenAxisPressed(m_driverController, 3, new ClawClose());
  WhenAxisReleased(m_driverController, 3, new ClawOpen());

  WhileAxisHeld(m_driverController, 2, new CargoEject());

  // WhenPressed(m_manipulatorController2, 6, new ClimbStage1());

  // m_driverController->SetRumble(frc::GenericHID::kLeftRumble, 1.0);
}

std::pair<double, double> OI::getSteeringControls() {
  double speed = m_driverController->GetY(frc::XboxController::JoystickHand::kLeftHand) * -1;
  double rotation = m_driverController->GetX(frc::XboxController::JoystickHand::kRightHand);

  // if (m_driverController->GetTriggerAxis(frc::XboxController::JoystickHand::kRightHand) < 0.5) {
  if (m_driverController->GetBumper(frc::XboxController::JoystickHand::kRightHand) == false) {
    return std::make_pair(speed, rotation * 0.75);
  }
  else {
    if (rotation > 0) {
      return std::make_pair(speed * 0.6, std::sqrt(rotation * 2 - std::pow(rotation, 2)));
    } 
    else {
      return std::make_pair(speed * 0.6, (std::sqrt(rotation * -2 - std::pow(rotation, 2)) * -1));
    }
  }
}
