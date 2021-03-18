#include "Intake.h"
#include "Commands/AutoAdjust.hpp"

Intake::Intake() :
	PIDSubsystem("Intake", 5.0, 1.0, 0.0),
	m_axleTalon(kAxleTalon),
	m_wheelTalon(kWheelTalon),
	m_internalTalon(kInternalTalon),
	m_axleEnc(2, 1.0, 0.0) //first arg was kChannelA
//	m_pidLoop(kP, kI, kD, &m_axleEnc, &m_axleTalon)
	//m_degrees(0.0)
{
	GetPIDController()->SetContinuous(true);
	SetAbsoluteTolerance(0.1);

	SetInputRange(0.0, 1.0); //try (0.0, 360.0)
	SetOutputRange(0.0, 1.0); //try (0.0, 220.0)

	SetSetpoint(DefaultPosition::kValue);
	Enable();
}

double Intake::ReturnPIDInput()
{
	return m_axleEnc.Get();
}

void Intake::UsePIDOutput(double output)
{
	m_axleTalon.PIDWrite(output);
}
/*
float Intake::GetPID()
{
	return m_pidLoop.Get();
}

void Intake::SetPID(float p, float i, float d)
{
	m_pidLoop.SetPID(p, i, d);
}

void Intake::SetSetpoint(float point)
{
	m_pidLoop.SetSetpoint(point);
}

double Intake::GetEncoderValue()
{
	return m_axleEnc.Get();
}
*/
//float Intake::ConvertToDegrees(float voltage)
//{
//	return m_degrees;
//}

void Intake::InitDefaultCommand()
{
	SetDefaultCommand(new AutoAdjust());
}
void Intake::SetAxleForward()
{
	m_axleTalon.Set(0.5, 0);
}

void Intake::SetAxleBackward()
{
	m_axleTalon.Set(-0.5, 0);
}

void Intake::SetAxleStopped()
{
	m_axleTalon.Set(0.0, 0);
}

void Intake::SetWheelForward()
{
	m_wheelTalon.Set(1.0, 0);
}

void Intake::SetWheelBackward()
{
	m_wheelTalon.Set(-1.0, 0);
}

void Intake::SetWheelStopped()
{
	m_wheelTalon.Set(0.0, 0);

	// StopMotor() was causing issues...

	//m_wheelTalon.Disable();
	//m_wheelTalon.StopMotor();
}

void Intake::SetWheelSlow()
{
	m_wheelTalon.Set(-0.15, 0);
}


void Intake::SetInternalForward(float set)
{
	m_internalTalon.Set(set, 0);
}

void Intake::SetInternalBackward(float set)
{
	m_internalTalon.Set(-set, 0);
}

void Intake::SetInternalStopped()
{
	m_internalTalon.Set(0.0, 0);
}

void Intake::init()
{
	m_wheelTalon.Set(0.0, 0);
	m_axleTalon.Set(0.0, 0);
	m_internalTalon.Set(0.0, 0);

	m_initialEnc = GetPosition();


	//m_wheelTalon.SetSpeed(0.0);
	//m_axleTalon.StopMotor();
	//m_wheelTalon.Disable();
	//m_wheelTalon.EnableDeadbandElimination(true);
	//m_axleEnc.SetPIDSourceType(PIDSourceType::kDisplacement);
	//m_pidLoop.SetOutputRange(-0.5, 0.5);

}
