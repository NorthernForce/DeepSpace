#include "Delay.h"
#include <WPILib.h>

Delay::Delay(): Timer()
{
	m_seconds = double(0);

}

Delay::Delay(const float sec): Timer(), m_seconds(double(sec))
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	//m_seconds = sec;
}

void Delay::Initialize()
{
	//requires("ArcadeDrive");
}

void Delay::Execute()
{
	Wait(m_seconds);
}

void Delay::End()
{

}

bool Delay::IsFinished()
{
	return true;
}

void Delay::Interrupted()
{

}
