#include "Flashlight.h"

Flashlight::Flashlight() :
		Subsystem("Flashlight"),
		m_relayA(0),
		m_relayB(0)
{
	m_relayA = new Relay(2);
	m_relayA->Set(Relay::kOn);
	m_relayA->Set(Relay::kForward);

	m_relayB = new Relay(1);
	m_relayB->Set(Relay::kOn);
	m_relayB->Set(Relay::kForward);
}

void Flashlight::TurnOn()
{
	m_relayA->Set(Relay::kOn);
	m_relayA->Set(Relay::kForward);

	m_relayB->Set(Relay::kOn);
	m_relayB->Set(Relay::kForward);
}

void Flashlight::TurnOff()
{
	m_relayA->Set(Relay::kOff);

	m_relayB->Set(Relay::kOff);
}

void Flashlight::init()
{
	m_relayA->Set(Relay::kOn);
	m_relayA->Set(Relay::kForward);

	m_relayB->Set(Relay::kOn);
	m_relayB->Set(Relay::kForward);
}

void Flashlight::Get()
{
	double outputA = m_relayA->Get();
	double outputB = m_relayB->Get();

	SmartDashboard::PutNumber("Lights", outputA);
	SmartDashboard::PutNumber("Lights", outputB);
}




