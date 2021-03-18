#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "WPILib.h"
#include "RobotMap.h"


class Climber: public PIDSubsystem
{
	private:

		Talon 					m_climbTalon;
		Talon     				m_reelTalon;
		AnalogPotentiometer     m_climbEnc;
		AnalogPotentiometer		m_reelEnc;

	protected:
		double ReturnPIDInput();
		void UsePIDOutput(double output);

	public:
		Climber();

		void SetClimberForward();
		void SetClimberBackward();
		void SetClimberStopped();
		void SetReelForward();
		void SetReelBackward();
		void SetReelStopped();
		void init();

};
