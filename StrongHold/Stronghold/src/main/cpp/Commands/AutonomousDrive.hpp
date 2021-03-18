#pragma once

#include "Commands/Command.h"
#include "../Main.h"
#include "../RobotMap.h"

class DriveStraight{};
class DriveStraight2{};
class DriveTurn{};
class VectorDriveToRobot{};
class VectorDriveToField{};
class RangeDrive{};

template<class Mode>
class AutonomousDrive : public Command
{
public:
	AutonomousDrive(float duration, float speed, float distance, float angle) :
		m_duration(duration),
		m_speed(speed),
		m_distance(distance),
		m_angle(angle),
		m_initialAngle(0),
		m_x(0),
		m_y(0)
	{
		Requires(&Main::getDrive());
		//Requires(&Main::getGyroSensor());
		Requires(&Main::getIntake());
	}

	void Initialize() override
	{
		m_timer.Reset();
		m_timer.Start();

		Main::getIntake().Disable();

		Main::getGyroSensor().Zero();
		Main::getDrive().ResetRight();
		Main::getDrive().ResetLeft();
		m_initialAngle = Main::getGyroSensor().GetAngle();

		Main::getDrive().SetDistancePerPulse();

		specificInit(Mode());
	}

	void specificInit(const DriveStraight& mode)
	{
		Main::getDrive().DriveArcade(m_speed, 0.0, true);
	}

	void specificInit(const DriveStraight2& mode)
	{
		Main::getDrive().DriveArcade(m_speed, 0.0, true);
	}

	void specificInit(const DriveTurn& mode)
	{
		Main::getDrive().DriveArcade(0.0, -m_speed, true);
	}

	void specificInit(const VectorDriveToRobot& mode)
	{
		Main::getDrive().DriveArcade(m_speed, -m_speed, true);
	}

	void specificInit(const VectorDriveToField& mode)
	{
		Main::getDrive().DriveArcade(m_speed, -m_speed, true);
	}

	void specificInit(const RangeDrive& mode)
	{
		Main::getDrive().DriveArcade(m_speed, 0.0, true);
	}

	void Execute() override
	{
		Main::getDrive().PutEncoderValues();

		specificExecute(Mode());
	}

	void specificExecute(const DriveStraight& mode)
	{
		if (Main::getDrive().GetLeftDistance() < m_distance) // Right encoder is currently giving strange values
		{
			float angle = Main::getGyroSensor().GetAngle();
			Main::getDrive().DriveArcade(m_speed, -(m_initialAngle - angle) * 0.05, true);
			Wait(0.01);
		}
		if (Main::getDrive().GetLeftDistance() > m_distance) // Right encoder is currently giving strange values
		{
			Main::getDrive().DriveArcade(0.0, 0.0, true);
		}
	}


	void specificExecute(const DriveStraight2& mode)
	{
		if (Main::getDrive().GetLeftDistance() < m_distance) // Right encoder is currently giving strange values
		{
			float angle = Main::getGyroSensor().GetAngle();
			Main::getDrive().DriveArcade(m_speed, -(m_initialAngle - angle) * 0.05, true);
			Wait(0.01);
		}
		if (Main::getDrive().GetLeftDistance() > m_distance) // Right encoder is currently giving strange values
		{
			Main::getDrive().DriveArcade(0.0, 0.0, true);
		}
	}

	void specificExecute(const DriveTurn& mode)
	{
		if (Main::getGyroSensor().GetAngle() - m_initialAngle > m_angle)
		{
			Main::getDrive().DriveArcade(0.0, 0.0, true);
		}
	}

	void specificExecute(const VectorDriveToRobot& mode)
	{
		m_x = m_x + cos(m_initialAngle - Main::getGyroSensor().GetAngle()) * Main::getDrive().GetYVel(); // times velocity
		m_y = m_y + sin(m_initialAngle - Main::getGyroSensor().GetAngle()) * Main::getDrive().GetXVel();
	}

	void specificExecute(const VectorDriveToField& mode)
	{

	}


	void specificExecute(const RangeDrive& mode)
	{
		double d = Main::getUltrasonicSensor().GetRangeInInches();
		float dist = float(d);

		SmartDashboard::PutNumber("Ultrasonic", d);

		SmartDashboard::PutNumber("Dist", dist);


//		if (dist < m_distance)
		{
//			float angle = Main::getGyroSensor().GetAngle();
//			Main::getDrive().DriveArcade(m_speed, -(m_initialAngle - angle) * 0.05, true);
			Main::getDrive().DriveArcade(0.6, 0.0, true);
			Wait(0.01);
		}

		if (dist >= m_distance)
		{
			Main::getDrive().DriveArcade(0.0, 0.0, true);
		}

	}




	bool IsFinished() override
	{
		return m_timer.HasPeriodPassed(m_duration);
	}

	void End() override
	{
		Main::getDrive().DriveArcade(0, 0, true);
	}

	void Interrupted() override
	{
		Main::getDrive().DriveArcade(0, 0, true);
	}

private:
	const double m_duration;
	const float m_speed;
	const float m_distance;
	const float m_angle;
	float m_initialAngle; // first reading, reference
	double m_x;
	double m_y;

	Timer m_timer;
};

