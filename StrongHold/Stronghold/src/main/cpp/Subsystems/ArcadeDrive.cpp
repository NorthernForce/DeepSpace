#include "ArcadeDrive.h"
#include "../RobotMap.h"

ArcadeDrive::ArcadeDrive() :
		SubsystemWithCommand<DriveWithJoystick>("ArcadeDrive"),
		m_drive(m_frontLeft, m_backLeft, m_frontRight, m_backRight),
		m_frontLeft(kFrontLeftTalon),
		m_frontRight(kFrontRightTalon),
		m_backLeft(kBackLeftTalon),
		m_backRight(kBackRightTalon),
		m_encRight(3, 2, false, Encoder::EncodingType::k1X),
		m_encLeft(0, 1, false, Encoder::EncodingType::k1X),
		P(0.50),
		I(0.02),
		D(0.00)
{
	m_drive.SetSafetyEnabled(false);
}

void ArcadeDrive::InitDefaultCommand()
{
	SetDefaultCommand(new DriveWithJoystick());
}

void ArcadeDrive::DriveArcade(float x, float y, bool z)
{
	m_drive.ArcadeDrive(x, y, z);
}

void ArcadeDrive::init()
{
	m_drive.SetSafetyEnabled(false);
//	m_frontLeft.SetSafetyEnabled(true);
//	m_backLeft.SetSafetyEnabled(true);
//	m_frontRight.SetSafetyEnabled(true);
//	m_backRight.SetSafetyEnabled(true);

	m_drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, false); //were flipped
	m_drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, false);
	m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,  false);
	m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,  false);

	m_drive.SetExpiration(0.1);
//	m_frontLeft.SetExpiration(0.5);
//	m_backLeft.SetExpiration(0.5);
//	m_frontRight.SetExpiration(0.5);
//	m_backRight.SetExpiration(0.5);

	DisableEncoders();

	m_encRight.SetDistancePerPulse(kDistancePerPulse); // kDistancePerPulse in mm
	m_encRight.SetDistancePerPulse(kDistancePerPulse);


}


void ArcadeDrive::EnableEncoders(bool invertGains)
{
	// When encoders are enabled, all motors must be inverted from
	// what they normaly would be.
	m_drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	m_drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,  true);
	m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,  true);
	// Set max output to be max drive rpm, since the Talons read
	// the encoder speed in rpm.
	m_drive.SetMaxOutput(kMaxDriveRPM);

	// Disable encoders, if already enabled.
	// Not sure this is necessary.
	m_frontLeft.Disable();
	m_backLeft.Disable();
	m_frontRight.Disable();
	m_backRight.Disable();

	// Max voltage should be 12V (Robot has 12V battery).
	m_frontLeft.ConfigMaxOutputVoltage(kMaxDriveVoltage);
	m_backLeft.ConfigMaxOutputVoltage(kMaxDriveVoltage);
	m_frontRight.ConfigMaxOutputVoltage(kMaxDriveVoltage);
	m_backRight.ConfigMaxOutputVoltage(kMaxDriveVoltage);

	// To use the encoders, we need to be in either
	// speed mode or position mode. For driving the
	// robot, speed mode makes more sense.
	m_frontLeft.SetControlMode(CANTalon::kSpeed);
	m_frontLeft.Set(10.0);
	m_backLeft.SetControlMode(CANTalon::kSpeed);
	m_backLeft.Set(10.0);
	m_frontRight.SetControlMode(CANTalon::kSpeed);
	m_frontRight.Set(10.0);
	m_backRight.SetControlMode(CANTalon::kSpeed);
	m_backRight.Set(10.0);

	// Fetch PID gains from the smart dashboard.
	P = SmartDashboard::GetNumber("P", 0);
	I = SmartDashboard::GetNumber("I", 0);
	D = SmartDashboard::GetNumber("D", 0);

	// Set proportional, integral and derivative gains,
	// inverting if appropriate.
	if(invertGains)
	{
		m_frontLeft.SetPID(-P, -I, -D);
		m_backLeft.SetPID(-P, -I, -D);
		m_frontRight.SetPID(-P, -I, -D);
		m_backRight.SetPID(-P, -I, -D);
	}
	else
	{
		m_frontLeft.SetPID(P, I, D);
		m_backLeft.SetPID(P, I, D);
		m_frontRight.SetPID(P, I, D);
		m_backRight.SetPID(P, I, D);
	}

	// We have quadrature encoders
	m_frontLeft.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_backLeft.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_frontRight.SetFeedbackDevice(CANTalon::QuadEncoder);
	m_backRight.SetFeedbackDevice(CANTalon::QuadEncoder);

	// Set encoder pulses per rev
	m_frontLeft.ConfigEncoderCodesPerRev(kEncoderPulsesPerRev);
	m_backLeft.ConfigEncoderCodesPerRev(kEncoderPulsesPerRev);
	m_frontRight.ConfigEncoderCodesPerRev(kEncoderPulsesPerRev);
	m_backRight.ConfigEncoderCodesPerRev(kEncoderPulsesPerRev);

	// Enable encoder control with the parameters above.
	m_frontLeft.EnableControl();
	m_backLeft.EnableControl();
	m_frontRight.EnableControl();
	m_backRight.EnableControl();
}

void ArcadeDrive::DisableEncoders()
{
	// Motors have to be inverted for using encoders, so they have
	// to be set back for kPercentVbus mode.
	m_drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor,   false); //were flipped
	m_drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, false);
	m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,    false);
	m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,  false);

	// Output values for kPercentVbus mode are -1..1, so
	// max output should be 1.0
	m_drive.SetMaxOutput(1.0);

	// Change mode to kPercentVbus.
	m_frontLeft.SetControlMode(CANTalon::kPercentVbus);
	m_backLeft.SetControlMode(CANTalon::kPercentVbus);
	m_frontRight.SetControlMode(CANTalon::kPercentVbus);
	m_backRight.SetControlMode(CANTalon::kPercentVbus);

	// Enable the talons
	m_frontLeft.Enable();
	m_backLeft.Enable();
	m_frontRight.Enable();
	m_backRight.Enable();
}

void ArcadeDrive::FlipDrive(bool flip)
{
	if (flip)
	{
		m_drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		m_drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,  true);
		m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,  true);
	}

	else
	{
		m_drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, false);
		m_drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, false);
		m_drive.SetInvertedMotor(RobotDrive::kRearLeftMotor,  false);
		m_drive.SetInvertedMotor(RobotDrive::kRearRightMotor,  false);
	}
}


float ArcadeDrive::GetRightDistance()
{

	return m_encRight.GetDistance();
}

float ArcadeDrive::GetLeftDistance()
{
	return m_encLeft.GetDistance();
}

double ArcadeDrive::GetYVel()
{
	double vel = kWheelRadius*(m_frontLeft.GetSpeed() + m_frontRight.GetSpeed()) / 2;
	return vel;
}

double ArcadeDrive::GetXVel()
{
	double vel = kWheelRadius*(abs(m_frontLeft.GetSpeed() - m_frontRight.GetSpeed())) / 2;
	return vel;
}

void ArcadeDrive::ResetRight()
{
	m_encRight.Reset();
}

void ArcadeDrive::ResetLeft()
{
	m_encLeft.Reset();
}

void ArcadeDrive::PutEncoderValues()
{
	SmartDashboard::PutNumber("Right Encoder:", m_encRight.GetDistance());
	SmartDashboard::PutNumber("Left Encoder:", m_encLeft.GetDistance());
}

void ArcadeDrive::SetDistancePerPulse()
{
	m_encRight.SetDistancePerPulse(kDistancePerPulse);
	m_encLeft.SetDistancePerPulse(kDistancePerPulse);
}
