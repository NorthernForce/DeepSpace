#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "Commands/DriveWithJoystick.h"
#include "WPILib.h"
#include "C:\Users\jcrosby\wpilib\user\cpp\include\ctre\phoenix\motorcontrol\can\WPI_TalonSRX.h"


class ArcadeDrive: public SubsystemWithCommand<DriveWithJoystick>
{
	private:

		RobotDrive m_drive;

		CANTalon m_frontLeft;
		CANTalon m_frontRight;
		CANTalon m_backLeft;
		CANTalon m_backRight;

		Encoder m_encRight;
		Encoder m_encLeft;

		double P;
		double I;
		double D;

	public:
		ArcadeDrive();
		void InitDefaultCommand();
		void DriveArcade(float x, float y, bool z);
		void init();
		void EnableEncoders(bool invertGains = true);
		void DisableEncoders();
		void FlipDrive(bool flip);
		float GetRightDistance();
		float GetLeftDistance();
		double GetYVel();
		double GetXVel();
		void ResetRight();
		void ResetLeft();
		void PutEncoderValues();
		void SetDistancePerPulse();
};

