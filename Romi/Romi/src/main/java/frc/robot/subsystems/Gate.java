// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot.subsystems;

import edu.wpi.first.wpilibj.Servo;
import edu.wpi.first.wpilibj2.command.SubsystemBase;
import frc.robot.Constants;

public class Gate extends SubsystemBase {
  /** Creates a new Gate. */
  private final Servo front = new Servo(Constants.kFrontGateServoPort);
  private final Servo rear  = new Servo(Constants.kRearGateServoPort);

  public Gate()
  {
    front.set( Constants.kDownAngle );
    rear.set( Constants.kDownAngle );
  }

  @Override
  public void periodic() 
  {
    
  }

  public void liftRear()
  {
    rear.setAngle( Constants.kUpAngle);
  }

  
  public void liftFront()
  {
     front.setAngle( Constants.kUpAngle);
  }


  public void lowerRear()
  {
    rear.setAngle( Constants.kDownAngle);
  }

  
  public void lowerFront()
  {
    front.setAngle( Constants.kDownAngle);
  }


  public void setFront(double pAngle)
  {
    front.setAngle(pAngle);
  }

  
  public void setRear(double pAngle)
  {
    rear.setAngle(pAngle);
  }

}
