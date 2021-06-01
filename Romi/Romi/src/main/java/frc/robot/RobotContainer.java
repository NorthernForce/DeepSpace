// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot;

import edu.wpi.first.wpilibj.GenericHID;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.XboxController;
import frc.robot.commands.ArcadeDrive;
import frc.robot.commands.AutonomousDistance;
import frc.robot.commands.AutonomousTime;
import frc.robot.subsystems.Drivetrain;
import frc.robot.subsystems.OnBoardIO;
import frc.robot.subsystems.OnBoardIO.ChannelMode;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj2.command.Command;
import edu.wpi.first.wpilibj2.command.PrintCommand;
import edu.wpi.first.wpilibj2.command.button.Button;
import edu.wpi.first.wpilibj2.command.button.JoystickButton;
import frc.robot.subsystems.Gate;

/////////////////////////////////////////////////////////////////////
//Changes for Direct Calls for Gate Up and Down Commands
//import frc.robot.commands.LiftGate;
import frc.robot.commands.FrontGateDown;
import frc.robot.commands.FrontGateUp;
import frc.robot.commands.RearGateDown;
import frc.robot.commands.RearGateUp;
////////////////////////////////////////////////////////////////////


/**
 * This class is where the bulk of the robot should be declared. Since Command-based is a
 * "declarative" paradigm, very little robot logic should actually be handled in the {@link Robot}
 * periodic methods (other than the scheduler calls). Instead, the structure of the robot (including
 * subsystems, commands, and button mappings) should be declared here.
 */
public class RobotContainer {
  // The robot's subsystems and commands are defined here...
  private final Drivetrain m_drivetrain = new Drivetrain();
  private final OnBoardIO m_onboardIO = new OnBoardIO(ChannelMode.INPUT, ChannelMode.INPUT);

/////////////////////////////////////////////////////////////////////////
  private final Gate m_gate = new Gate();

/////////////////////////////////////////////////////////////////////////
  //Added for Proportional Control of each axis
  private ProportionControl m_axisProp0 = new ProportionControl();
  private ProportionControl m_axisProp1 = new ProportionControl();
//  private ProportionControl m_axisProp3 = new ProportionControl();
//////////////////////////////////////////////////////////////////////////

  // Assumes a gamepad plugged into channnel 0
  private final Joystick m_controller = new Joystick(0);

  // Create SmartDashboard chooser for autonomous routines
  private final SendableChooser<Command> m_chooser = new SendableChooser<>();

  // NOTE: The I/O pin functionality of the 5 exposed I/O pins depends on the hardware "overlay"
  // that is specified when launching the wpilib-ws server on the Romi raspberry pi.
  // By default, the following are available (listed in order from inside of the board to outside):
  // - DIO 8 (mapped to Arduino pin 11, closest to the inside of the board)
  // - Analog In 0 (mapped to Analog Channel 6 / Arduino Pin 4)
  // - Analog In 1 (mapped to Analog Channel 2 / Arduino Pin 20)
  // - PWM 2 (mapped to Arduino Pin 21)
  // - PWM 3 (mapped to Arduino Pin 22)
  //
  // Your subsystem configuration should take the overlays into account

  /** The container for the robot. Contains subsystems, OI devices, and commands. */
  public RobotContainer() {
    // Configure the button bindings
    configureButtonBindings();
  }

  /**
   * Use this method to define your button->command mappings. Buttons can be created by
   * instantiating a {@link GenericHID} or one of its subclasses ({@link
   * edu.wpi.first.wpilibj.Joystick} or {@link XboxController}), and then passing it to a {@link
   * edu.wpi.first.wpilibj2.command.button.JoystickButton}.
   */
  private void configureButtonBindings() {
    // Default command is arcade drive. This will run unless another command
    // is scheduled over it.
    m_drivetrain.setDefaultCommand(getArcadeDriveCommand());

    

    // Example of how to use the onboard IO
    Button onboardButtonA = new Button(m_onboardIO::getButtonAPressed);
    onboardButtonA
        .whenActive(new PrintCommand("Button A Pressed"))
        .whenInactive(new PrintCommand("Button A Released"));

///////////////////////////////////////////////////////////////////////////////////
// Needed for return value on JoystickButton "whenPressed" Method Calls
    Button whenPressed;
///////////////////////////////////////////////////////////////////////////////////

    JoystickButton frontGateUp = new JoystickButton(m_controller, Constants.kFrontUpButton);
    JoystickButton frontGateDown = new JoystickButton(m_controller, Constants.kFrontDownButton);

    JoystickButton rearGateUp = new JoystickButton(m_controller, Constants.kRearUpButton);
    JoystickButton rearGateDown = new JoystickButton(m_controller, Constants.kRearDownButton);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////// Remove ListGate Command and try direct call to Direct Commands
    //
    //m_gate.setDefaultCommand(new LiftGate(frontGateUp, frontGateDown, rearGateUp, rearGateDown, m_gate));
    whenPressed = frontGateUp.whenPressed(new FrontGateUp(m_gate), true);
    whenPressed = frontGateDown.whenPressed(new FrontGateDown(m_gate), true);

    whenPressed = rearGateUp.whenPressed(new RearGateUp(m_gate), true);
    whenPressed = rearGateDown.whenPressed(new RearGateDown(m_gate), true);
////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Setup SmartDashboard options
    m_chooser.setDefaultOption("Auto Routine Distance", new AutonomousDistance(m_drivetrain));
    m_chooser.addOption("Auto Routine Time", new AutonomousTime(m_drivetrain));
    SmartDashboard.putData(m_chooser);
  }

  /**
   * Use this to pass the autonomous command to the main {@link Robot} class.
   *
   * @return the command to run in autonomous
   */
  public Command getAutonomousCommand() 
  {
    return m_chooser.getSelected();
  }

  /**
   * Use this to pass the teleop command to the main {@link Robot} class.
   *
   * @return the command to run in teleop
   */
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Arcade Drive Axiis Below are for PS2 Controller  -- Need to be changed for X-Box Controller
  //Modiied Arcade Drive with 50% Axis for turn on Forward / Reverse Axis 
  public Command getArcadeDriveCommand() {
    return new ArcadeDrive(
        m_drivetrain, () -> m_axisProp0.prop(-m_controller.getRawAxis(1)), () -> m_axisProp1.prop((m_controller.getRawAxis(4) + (m_controller.getRawAxis(0)) / 2)));
        
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

