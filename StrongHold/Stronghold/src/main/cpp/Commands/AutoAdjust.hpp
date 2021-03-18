#pragma once

#include "Commands/Command.h"
#include "../Main.h"


class AutoAdjust: public Command
{
	public:
		AutoAdjust() :
			m_finished(false)
		{
			Requires(&Main::getIntake());
			Requires(&Main::getOpticalSensors());
		}

		virtual void Initialize()
		{
			m_finished = false;
		}

		virtual void Execute()
		{
			if (Main::getOpticalSensors().GetSensorFront() == 0.0)
			{
				Main::getIntake().SetInternalBackward(0.2);
			}

			if (Main::getOpticalSensors().GetSensorBack() == 0.0)
			{
				Main::getIntake().SetInternalForward(0.2);
			}

			m_finished = Main::getOpticalSensors().GetSensorBack() && Main::getOpticalSensors().GetSensorFront();
		}


		virtual bool IsFinished() { return m_finished; }
		virtual void End()
		{
			Main::getIntake().SetInternalStopped();
		}

		virtual void Interrupted()
		{
			Main::getIntake().SetInternalStopped();
		}

	private:
		bool  m_finished;
};

