// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
// FRC Team 172 - JJC
////////////////////////////////////////////////////////////////////////////
// dMotor to Control one half of a Toshiba TB6612FNG Based Motor Contrpoller
//
// Inception: June 11, 2021
//
// FRC Team 172 - JJC
////////////////////////////////////////////////////////////////////////////
//Change Log
//
////////////////////////////////////////////////////////////////////////////

package frc.robot.subsystems;

import edu.wpi.first.wpilibj2.command.SubsystemBase;
import edu.wpi.first.wpilibj.DigitalOutput;
import edu.wpi.first.wpilibj.PWM;
import frc.robot.Constants;
import java.lang.Math;

public class dMotor extends SubsystemBase {
  /** Creates a new dMotor. */
  private edu.wpi.first.wpilibj.DigitalOutput m_In1;  //Control Input 1 Digital Output
  private edu.wpi.first.wpilibj.DigitalOutput m_In2;  //Control Input 2 Digital Output 
  private edu.wpi.first.wpilibj.PWM m_PWM;  //PWM Port
  private edu.wpi.first.wpilibj.DigitalOutput m_Stby; //Stand By Port
  private double m_Multiplier;  // Scaling Factor
  private char m_Direction; // Current Direction 
  private double m_Speed;   // Current Speed setting


  //Constanrts to Control dMotor Class State
  final static public char kForward = 'F';    // CW Rotation
  final static public char kReverse = 'R';    // CCW Rotation
  final static public char kStop    = 'S';    // Stop Controller (Coast ?)
  final static public char kBrake   = 'B';    // Brake Mode
  final static public char kStandby = 'X';    // Standby Mode (Settable if m_Stby not equal to 0)
  final static public char kActive  = 'A';


  public dMotor(int In1, int In2, int PWM, int Stby, double Mult) 
  {
    // Set the Class Objects Member Atrtrributes on ( = Class State) upon instantiation.
    m_In1 = new DigitalOutput(In1);
    m_In2 = new DigitalOutput(In2);
    m_PWM = new PWM(PWM);
    m_Multiplier = Mult;
    m_Direction = kForward;

    if (Stby > 0)
        m_Stby = new edu.wpi.first.wpilibj.DigitalOutput(Stby);

    m_Speed = 0;

    setMode(kStop);

  }

  
//  public dMotor(int In1, int In2, int PWM, double Mult)
//   {
//      dMotor(In1, In2, PWM, 0, Mult);
//   }

//Set the "Meta State" of the Controller.
//Note: Active and Standby are reciprocal and mutually exclusive using the Standby Pin (if instantiated)
//      Forward, Reverse, Brake, and Stop are Mutually exclusive using the Input 1 and Input 2 Pins
  public void setMode(char pState)
  {
    switch (pState) 
    {
      case kActive:
        Active();
        break;

      case kBrake:
        Brake();
        break;

      case kForward:  
        Forward();
        break;
                     
      case kReverse:
        Reverse();
        break;

      case kStop:
        Stop();
        break;

      case kStandby:
        Standby();
        break;
    
      default:
        break;
    }
  }

  private void Forward()
  {
    m_In1.set(true);
    m_In2.set(false);
  }

  private void Reverse()
  {
    m_In1.set(false);
    m_In2.set(true);
  }

  private void Stop()
  {
    m_In1.set(false);
    m_In2.set(false);
  }

  private void Brake()
  {
    m_In1.set(true);
    m_In2.set(true);
  }

  private void Standby()
  {
    if (m_Stby.getChannel() != 0)
      m_Stby.set(true); 
  }

  private void Active()
  {
    if (m_Stby.getChannel() != 0)
    m_Stby.set(false);
  }

  public void setSpeed(double Speed)
  {
    if (Math.abs(Speed) > 1)
      m_Speed = 1;
    else
      m_Speed = Math.abs(Speed);

    m_PWM.setSpeed(m_Speed);
  }

  public double getSpeed()
  {
    return m_Speed;
  }

  @Override
  public void periodic() 
  {
    // This method will be called once per scheduler run
  }
}