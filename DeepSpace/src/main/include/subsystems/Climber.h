
#pragma once
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Climber: public frc::Subsystem
{
public:
  Climber();
  void InitDefaultCommand() override;
  void lower();
  void lowerExplicit(double target);
  void raise();
  void stop();
  void limitCurrent(WPI_TalonSRX&);
  bool atLowerLimit();
  bool atUpperLimit();
    
private:
  std::shared_ptr<WPI_TalonSRX> m_masterTalonLifter;
  std::shared_ptr<WPI_TalonSRX> m_slaveTalonLifter;

  constexpr static auto k_timeout = 0;
  constexpr static auto k_peakCurrent = 22;
  constexpr static auto k_continuousCurrent = 11;
  constexpr static auto k_peakCurrentDuration = 2000;
  
  const double k_forwardMotorSpeed = 0.5;
  const double k_reverseMotorSpeed = -0.5;
};
