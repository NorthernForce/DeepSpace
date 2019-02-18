/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

std::shared_ptr<OI> Robot::m_oi;
std::shared_ptr<BrushlessDrive> Robot::m_driveTrain;
std::shared_ptr<Claw> Robot::m_claw;
std::shared_ptr<LineTracker> Robot::m_lineTracker;
std::shared_ptr<UltrasonicSensor> Robot::m_ultrasonic;
std::shared_ptr<AHRS> Robot::m_ahrs;


void Robot::RobotInit() {
  std::cout << "RobotInit Started" << std::endl;

  m_oi.reset(new OI());

  // Initialize Subsystems
  m_driveTrain.reset(new BrushlessDrive());
  m_claw.reset(new Claw());
  m_lineTracker.reset(new LineTracker());
  m_ultrasonic.reset(new UltrasonicSensor());
  m_ahrs = std::make_unique<AHRS>(frc::SPI::Port::kMXP);
  
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  std::cout << "DisabledInit Started" << std::endl;
}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  std::cout << "AutonomousInit Started" << std::endl;
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  std::cout << "TeleopInit Started" << std::endl;
}

void Robot::TeleopPeriodic() { 
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif