// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

// package frc.robot.commands;

// import edu.wpi.first.wpilibj2.command.CommandBase;
// import edu.wpi.first.wpilibj2.command.button.Button;
// import edu.wpi.first.wpilibj2.command.button.JoystickButton;
// import frc.robot.subsystems.Gate;

// public class LiftGate extends CommandBase 
// {

// //  private final Gate m_gate = new Gate();
//   private final JoystickButton m_FrontUp;
//   private final JoystickButton m_FrontDown;
//   private final JoystickButton m_RearUp;
//   private final JoystickButton m_RearDown;
//   private Gate m_gate;
//   private Button whenPressed;

//   /** Creates a new LiftGate. */
//   public LiftGate(JoystickButton frontUp, JoystickButton frontDown, JoystickButton rearUp, JoystickButton rearDown, Gate gate) 
//   {
//     m_FrontUp   = frontUp;
//     m_FrontDown = frontDown;
//     m_RearUp    = rearUp;
//     m_RearDown  = rearDown;
    // m_gate      = gate;

//     // Use addRequirements() here to declare subsystem dependencies.
//     //addRequirements(m_gate);

//   }

//   // Called when the command is initially scheduled.
//   @Override
//   public void initialize() 
//   {

//   }

//   // Called every time the scheduler runs while the command is scheduled.
//   @Override
//   public void execute() 
//   {
//       whenPressed = m_FrontUp.whenPressed(new FrontGateUp(m_gate), true);
//       whenPressed = m_FrontDown.whenPressed(new FrontGateDown(m_gate), true);
//       whenPressed = m_RearUp.whenPressed(new RearGateUp(m_gate), true);
//       whenPressed = m_FrontDown.whenPressed(new RearGateDown(m_gate), true);

//   }

//   // Called once the command ends or is interrupted.
//   @Override
//   public void end(boolean interrupted) 
//   {


//   }

//   // Returns true when the command should end.
//   @Override
//   public boolean isFinished() 
//   {
//     return false;
//   }
// }
