#include "Climber.h"

Climber::Climber() :
	PIDSubsystem("Climber", 3.0, 0.0, 0.0),
	m_climbTalon(9),
	m_reelTalon(10),
	m_climbEnc(4, 5),
	m_reelEnc(6, 7)
{}

double Climber::ReturnPIDInput()
{
	return m_reelEnc.Get();
}

void Climber::UsePIDOutput(double output)
{
	m_reelTalon.PIDWrite(output);
}

void Climber::SetClimberForward()
{
	m_climbTalon.Set(1.0, 0);
}

void Climber::SetClimberBackward()
{
	m_climbTalon.Set(-1.0, 0);
}

void Climber::SetClimberStopped()
{
	m_climbTalon.Set(0.0, 0);
}

void Climber::SetReelForward()
{
	m_reelTalon.Set(1.0, 0);
}

void Climber::SetReelBackward()
{
	m_reelTalon.Set(-1.0, 0);
}

void Climber::SetReelStopped()
{
	m_reelTalon.Set(0.0, 0);
}




