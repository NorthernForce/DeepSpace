/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

class Elevator : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  std::shared_ptr<WPI_TalonSRX> m_primaryTalonElevator;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator1;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator2;
  std::shared_ptr<WPI_TalonSRX> m_followerTalonElevator3;
  std::shared_ptr<frc::Solenoid> m_elevatorExtenderSolenoid;
  std::shared_ptr<frc::Solenoid> m_elevatorRetracterSolenoid;

  int m_setpoint;

  bool m_isRetracted = true;

 public:
  Elevator();
  void InitDefaultCommand() override;
  void Periodic() override;
  void raise();
  void setSpeed(double speed);
  void lower();
  void stop();
  void setPosition(int);
  bool atSetpoint();
  void setHomePosition();
  bool atLowerLimit();
  void extend();
  void retract();
  void holdCurrentDeployment();
  bool isRetracted();
  int getSelectedSensorPosition();
  int getClosedLoopError();
  double getPGainValue();
  void enableForwardLimitSwitch();
  void disableForwardLimitSwitch();
  void enableReverseLimitSwitch();
  void disableReverseLimitSwitch();
  void startClimb();
  
  const static int timeoutMs;
	const static int noTimeoutMs;
	const static double freeSpeedRPM;
	const static double maxSpeedRPM;
	const static double sensorUnitsPerRev;
	const static double maxSensorUnitsPer100ms;
	const static double feedForwardGain;
	const static double pGainPower;
	const static double pGainError;
	const static double pGain;
	const static double iGain;
	const static double iLimit;
	const static double dGain;
	const static double timeToMaxSpeed;
	const static int slotIdx;
	const static int pidIdx;
	const static int defaultPeakAmps;
	const static int defaultContinuousCurrent;
	const static double rampTime;

  const static double k_elevatorMaxRaiseSpeed;
  const static double k_elevatorMaxLowerSpeed;

  const static double k_deployDelay;
  const static double k_motorStopDelay;

  const static int k_startingSetPoint;
};
