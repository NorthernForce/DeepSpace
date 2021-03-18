
#pragma once

#include "WPILib.h"
#include "RobotMap.h"

class Flashlight: public Subsystem
{

	public:
		Flashlight();
		void TurnOn();
		void TurnOff();
		void init();
		void Get();

	private:
		Relay *m_relayA;
		Relay *m_relayB;
};





