#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "WPILib.h"
#include "RobotMap.h"

class OpticalSensors: public Subsystem
{
	public:

		OpticalSensors();
		float GetSensorFront();
		float GetSensorBack();

	private:
		DigitalInput m_opticalFront;
		DigitalInput m_opticalBack;

};
