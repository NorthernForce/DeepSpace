#pragma once

#include "Commands/Command.h"
#include "../Main.h"


class ShootBall: public Command
{
	public:
		ShootBall() :
			m_finished(false)
		{
			Requires(&Main::getShooter());
			Requires(&Main::getIntake());
			//Requires(&Main::getOpticalSensors());
		}

		virtual void Initialize()
		{
			//Main::getShooter().Forward();
			m_finished = false;
		}

		virtual void Execute()
		{
			Main::getIntake().SetInternalForward(1.0);
			//Wait(4.0);
	    	m_finished = true;
		}


		virtual bool IsFinished() { return m_finished; }
		virtual void End()
		{
			Wait(1.0);
			Main::getShooter().Stopped();
			Main::getIntake().SetInternalStopped();
		}

		virtual void Interrupted()
		{
			Main::getShooter().Stopped();
			Main::getIntake().SetInternalStopped();
		}

	private:
		bool  m_finished;
};

