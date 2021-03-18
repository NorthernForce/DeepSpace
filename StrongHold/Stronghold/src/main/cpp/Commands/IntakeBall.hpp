#pragma once

#include "Commands/Command.h"
#include "../Main.h"


template<typename T>
class IntakeBall: public Command
{
	public:
		IntakeBall() :
			m_finished(false),
			m_axleMove(true),
			m_point(0.0)
		{
			Requires(&Main::getIntake());
			Requires(&Main::getOpticalSensors());

			 //Main::getOI().GetManipulatorStick().GetZ() +
			/*
			if (m_point > 1)
			{
				--m_point;
			}

			if (m_point < 0)
			{
				++m_point;
			}
			*/
		}

		virtual void Initialize()
		{
			Main::getIntake().Enable();
			float m_point = T::kValue;
			m_finished = false;
			Main::getIntake().SetSetpoint(m_point); //.4, was .7, should be DownPosition::kDegrees
		}

		virtual void Execute()
		{
			if (m_axleMove)
			{
				Main::getIntake().SetWheelBackward();
			}

			Main::getIntake().SetInternalForward(1.0);

			if (Main::getOpticalSensors().GetSensorBack() == 0)
			{
				Main::getIntake().SetWheelSlow();
				m_axleMove = false;
			}

			if (Main::getOpticalSensors().GetSensorFront() == 0)
			{
				Main::getIntake().SetInternalStopped();
				Main::getIntake().SetWheelStopped();
				m_finished = true;
			}
		}


		virtual bool IsFinished()
		{
			m_finished = Main::getOpticalSensors().GetSensorFront() == 0;

			return m_finished;
		}
		virtual void End()
		{
			Main::getIntake().SetWheelStopped();
			Main::getIntake().SetInternalStopped();
			//Main::getIntake().Disable();
		}

		virtual void Interrupted()
		{
			Main::getIntake().SetWheelStopped();
			Main::getIntake().SetInternalStopped();
			Main::getIntake().Disable();
		}

	private:
		bool  m_finished;
		bool  m_axleMove;
		float m_point;
};
