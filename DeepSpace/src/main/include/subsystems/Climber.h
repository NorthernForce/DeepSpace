
#pragma once
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Climber: public frc::Subsystem
{
public:
  Climber();
  void InitDefaultCommand() override;
  void lower();
  void setSpeed(double speed);
  void raise();
  void stop();
  void limitCurrent(WPI_TalonSRX&);
  bool atLowerLimit();
  bool atUpperLimit();

  const static int k_timeout;
  const static int k_peakCurrent;
  const static int k_continuousCurrent;
  const static int k_peakCurrentDuration;
  
  const static double k_forwardMotorSpeed;
  const static double k_reverseMotorSpeed;
    
private:
  std::shared_ptr<WPI_TalonSRX> m_masterTalonLifter;
  std::shared_ptr<WPI_TalonSRX> m_slaveTalonLifter;
};
