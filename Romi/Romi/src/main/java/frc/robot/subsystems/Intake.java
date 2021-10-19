// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot.subsystems;

import edu.wpi.first.wpilibj2.command.SubsystemBase;
import frc.robot.subsystems.dMotor;

public class Intake extends SubsystemBase {
  /** Creates a new Intake. */

  private dMotor m_Intake = new dMotor(8, 9, 2, 0, 1);
  private double m_speed;

  public Intake() 
  {
    m_Intake.setSpeed(1.0);                                                                                                                                                                                     

  }

  @Override
  public void periodic() 
  {
    // This method will be called once per scheduler run
  } 

  public void set(double speed)
  {
    m_speed = speed;
    m_Intake.setSpeed(m_speed);
  }

  public void forward()
  {
    m_Intake.setMode(dMotor.kActive);
    m_Intake.setMode(dMotor.kForward);
    set(1.0);
  }

  public void reverse()
  {
    m_Intake.setMode(dMotor.kActive);
    m_Intake.setMode(dMotor.kReverse);
    set(1.0);
  }

  public void stop()
  {
    set(0.0);
    m_Intake.setSpeed(dMotor.kBrake);
  }


}
