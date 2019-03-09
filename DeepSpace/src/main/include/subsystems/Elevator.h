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
  constexpr static int timeoutMs = 10;
	constexpr static int noTimeoutMs = 0;
	constexpr static double freeSpeedRPM = 18730;
	constexpr static double maxSpeedRPM = freeSpeedRPM * 0.80;
	constexpr static double sensorUnitsPerRev = 256 * 4; // The TalonSRX counts 4 edges per encoder count, the quadrature encoder has 12 counts per revolution
	constexpr static double maxSensorUnitsPer100ms = 1500; // sensorUnitsPerRev * maxSpeedRPM / 60 / 10;
	constexpr static double feedForwardGain = 0.3; // 1023 / maxSensorUnitsPer100ms;
	constexpr static double pGainPower = 0.15;
	constexpr static double pGainError = 100;
	constexpr static double pGain = 0.7; // (1023 * pGainPower) / pGainError;
	constexpr static double iGain = 0.007;
	constexpr static double iLimit = 1500;
	constexpr static double dGain = 0.07; //pGain / 10;
	constexpr static double timeToMaxSpeed = 0.75;
	constexpr static int slotIdx = 0;
	constexpr static int pidIdx = 0;
	constexpr static int defaultPeakAmps = 15;
	constexpr static int defaultContinuousCurrent = 12;
	constexpr static double rampTime = 0.5;

  bool m_isRetracted = true;

  const double k_elevatorRaiseSpeed = 0.5;
  const double k_elevatorLowerSpeed = -0.6;

 public:
  Elevator();
  void Raise();
  void LowerExplicit( double target );
  void Lower();
  void Stop();
  void InitDefaultCommand() override;
  void SetPosition(int);
  bool AtSetpoint();
  void SetHomePosition();
  bool AtLowerLimit();
  void Extend();
  void Retract();
  void HoldCurrentDeployment();
  bool IsRetracted();
  int GetSelectedSensorPosition();
  int GetClosedLoopError();
  double GetPGainValue();
  void EnableForwardLimitSwitch();
  void DisableForwardLimitSwitch();
  void EnableReverseLimitSwitch();
  void DisableReverseLimitSwitch();
};
