// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot.commands;

import edu.wpi.first.wpilibj2.command.InstantCommand;
import frc.robot.subsystems.Gate;

/** Add your docs here. */
public class FrontGateUp extends InstantCommand 
{
  private final Gate m_Gate = new Gate(); 
  /** Add your docs here. */
  public FrontGateUp() 
  {
    super();
    // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    //requires(m_Gate);
  }

  // Called once when the command executes
  @Override
  public void initialize() 
  {
    m_Gate.liftFront();
  }
}
