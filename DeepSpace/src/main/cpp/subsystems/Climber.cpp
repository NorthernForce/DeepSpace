
#include "subsystems/Climber.h"

#include <iostream>

#include "RobotMap.h"
#include "commands/ClimberDriveSlowWhileLowered.h"

Climber::Climber() : Subsystem("Climber") {
    m_masterTalonLifter.reset(new WPI_TalonSRX(RobotMap::Climber::k_leftClimbingMotor_id));
    m_slaveTalonLifter.reset(new WPI_TalonSRX(RobotMap::Climber::k_rightClimbingMotor_id));

    m_slaveTalonLifter->SetInverted(true);
    m_slaveTalonLifter->Follow(*m_masterTalonLifter);

    m_masterTalonLifter->ConfigForwardLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);
    m_masterTalonLifter->ConfigReverseLimitSwitchSource(LimitSwitchSource_FeedbackConnector, LimitSwitchNormal_NormallyOpen, 0);

    m_masterTalonWheels.reset(new WPI_TalonSRX (RobotMap::Climber::k_driveMotor_id));
}

void Climber::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  SetDefaultCommand(new ClimberDriveSlowWhileLowered());
}

void Climber::lowerExplicit(double target) {
    m_masterTalonLifter->Set(std::min(target, k_reverseMotorSpeed));
}

void Climber::lower() {
    m_masterTalonLifter->Set(k_reverseMotorSpeed);
}

void Climber::raise() {
    m_masterTalonLifter->Set(k_forwardMotorSpeed);
}

void Climber::stop() {
    m_masterTalonLifter->Set(0.0);
}

void Climber::driveWheels(double speed) {
    m_masterTalonWheels->Set(speed);
}

void Climber::driveForward() {
    driveWheels(k_driveForwardMotorSpeed);
}

void Climber::driveBackward() {
    driveWheels(k_driveBackwardMotorSpeed);
}

void Climber::driveStop() {
    driveWheels(0.0);
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