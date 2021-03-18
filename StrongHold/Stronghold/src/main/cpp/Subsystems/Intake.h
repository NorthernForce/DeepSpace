#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "WPILib.h"
#include "RobotMap.h"


class Intake: public PIDSubsystem
{
	private:

		CANTalon 				m_axleTalon;
		Talon 					m_wheelTalon;
		Talon     				m_internalTalon;
		AnalogPotentiometer     m_axleEnc;


	protected:
		double ReturnPIDInput();
		void UsePIDOutput(double output);

	public:
		Intake();

		void InitDefaultCommand();
		void SetAxleForward();
		void SetAxleBackward();
		void SetAxleStopped();
		void SetWheelForward();
		void SetWheelBackward();
		void SetWheelStopped();
		void SetWheelSlow();
		void SetInternalForward(float set);
		void SetInternalBackward(float set);
		void SetInternalStopped();
		void init();
		double			m_initialEnc;

};
