#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "WPILib.h"
#include "RobotMap.h"


class Shooter: public Subsystem
{
	private:
		CANTalon 	m_shooterTalon;
		Encoder 	m_shooterEnc;

	//protected:
		//double ReturnPIDInput();
		//void UsePIDOutput(double output);

	public:
		Shooter();
		void Forward();
		void Stopped();
		void init();
		float GetVoltage();
		double GetCurrent();
		bool IsShooterReady();
};
