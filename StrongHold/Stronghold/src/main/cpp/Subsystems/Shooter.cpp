#include "Shooter.h"

Shooter::Shooter() :
	Subsystem("Shooter"),//PIDSubsystem("Shooter", 2.0, 0.0, 0.0),
	m_shooterTalon(kShooterTalon),
	m_shooterEnc(7, 1.0, 0.0)
{
	//GetPIDController()->SetContinuous(true);
	//SetAbsoluteTolerance(0.1);
	//Enable();
}
/*
double Shooter::ReturnPIDInput()
{
	return m_shooterEnc.Get();
}

void Shooter::UsePIDOutput(double output)
{
	m_shooterTalon.PIDWrite(output);
}
*/
void Shooter::Forward()
{
	m_shooterTalon.Set(1.0, 0);
}

void Shooter::Stopped()
{
	m_shooterTalon.Set(0,0);
}

void Shooter::init()
{
	Stopped();
}

float Shooter::GetVoltage()
{
	return m_shooterTalon.GetOutputVoltage();
}

double Shooter::GetCurrent()
{
	return m_shooterTalon.GetOutputCurrent();
}

bool Shooter::IsShooterReady()
{
	if ((GetCurrent() > 4.1) && (GetVoltage() > 8))
	{
		return true;
	}

	else
	{
		return false;
	}
}
