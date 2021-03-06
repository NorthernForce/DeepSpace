
#include "subsystems/Climber.h"

#include <iostream>

#include "RobotMap.h"

const int Climber::k_timeout = 0;
const int Climber::k_peakCurrent = 35;
const int Climber::k_continuousCurrent = 25;
const int Climber::k_peakCurrentDuration = 2000;

const double Climber::k_forwardMotorSpeed = 0.5;
const double Climber::k_reverseMotorSpeed = 1; // abs of

Climber::Climber() : Subsystem("Climber") {
  m_masterTalonLifter.reset(new WPI_TalonSRX(RobotMap::Climber::k_primary_id));
  m_slaveTalonLifter.reset(new WPI_TalonSRX(RobotMap::Climber::k_follower_id));

  m_slaveTalonLifter->SetInverted(true);
  m_slaveTalonLifter->Follow(*m_masterTalonLifter);

  m_masterTalonLifter->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);
  m_masterTalonLifter->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

  frc::SmartDashboard::PutNumber("Climber: Raise Speed", k_forwardMotorSpeed);
  frc::SmartDashboard::PutNumber("Climber: Lower Speed", k_reverseMotorSpeed);
}

void Climber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
}

void Climber::setSpeed(double speed) {
  if (speed > 1) {
    // m_masterTalonLifter->Set(k_forwardMotorSpeed);
    m_masterTalonLifter->Set(frc::SmartDashboard::GetNumber("Climber: Raise Speed", k_forwardMotorSpeed));
  }
  else if (speed > 0) {
    // m_masterTalonLifter->Set(speed * k_forwardMotorSpeed);
    m_masterTalonLifter->Set(speed * frc::SmartDashboard::GetNumber("Climber: Raise Speed", k_forwardMotorSpeed));
  }
  else if (speed < -1) {
    // m_masterTalonLifter->Set(-1 * k_reverseMotorSpeed);
    m_masterTalonLifter->Set(-1 * frc::SmartDashboard::GetNumber("Climber: Lower Speed", k_reverseMotorSpeed));
  }
  else if (speed < 0) {
    // m_masterTalonLifter->Set(speed * k_reverseMotorSpeed);
    m_masterTalonLifter->Set(speed * frc::SmartDashboard::GetNumber("Climber: Lower Speed", k_reverseMotorSpeed));
  }
  else {
    m_masterTalonLifter->Set(0);
  }
}
void Climber::lower() {
  setSpeed(-1);
}
void Climber::raise() {
  setSpeed(1);
}
void Climber::stop() {
  setSpeed(0);
}

bool Climber::atUpperLimit() {
    return m_masterTalonLifter->GetSensorCollection().IsFwdLimitSwitchClosed(); // might have to switch rev and fwd
}

bool Climber::atLowerLimit() {
    return m_masterTalonLifter->GetSensorCollection().IsRevLimitSwitchClosed();
}

void Climber::limitCurrent(WPI_TalonSRX& controller) {
    controller.ConfigPeakCurrentLimit(k_peakCurrent, k_timeout);
    controller.ConfigContinuousCurrentLimit(k_continuousCurrent, k_timeout);
    controller.ConfigPeakCurrentDuration(k_peakCurrentDuration, k_timeout);
    controller.EnableCurrentLimit(true);
} 