
#pragma once
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Climber: public frc::Subsystem
{
public:
  Climber();
  void InitDefaultCommand() override;
  void Lower();
  void LowerExplicit(double target);
  void Raise();
  void Stop();
  void DriveWheels(double speed);
  void DriveForward();
  void DriveBackward();
  void DriveStop();
  void LimitCurrent(WPI_TalonSRX&);
  bool AtLowerLimit();
  bool AtUpperLimit();
    
private:
  std::shared_ptr<WPI_TalonSRX> m_masterTalonLifter;
  std::shared_ptr<WPI_TalonSRX> m_slaveTalonLifter;
  std::shared_ptr<WPI_TalonSRX> m_masterTalonWheels;

  constexpr static auto k_timeout = 0;
  constexpr static auto k_peakCurrent = 22;
  constexpr static auto k_continuousCurrent = 11;
  constexpr static auto k_peakCurrentDuration = 2000;
  
  constexpr static double k_forwardMotorSpeed = 0.5;
  constexpr static double k_reverseMotorSpeed = -0.5;
  constexpr static double k_driveForwardMotorSpeed = 0.5;
  constexpr static double k_driveBackwardMotorSpeed = -0.5;

};
