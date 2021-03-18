#pragma once

#include "Commands/Command.h"
#include "../Main.h"


template<typename T>
class SetAxlePosition: public Command
{
	public:
		SetAxlePosition() :
			m_finished(false),
			m_point(0.0)
		{
			Requires(&Main::getIntake());
		}
		virtual void Initialize()
		{
			/*
			float m_point = Main::getOI().GetManipulatorStick().GetZ() + T::kValue;
			if (m_point > 1)
			{
				--m_point;
			}

			if (m_point < 0)
			{
				++m_point;
			}
			*/

			m_point = T::kValue;
			Main::getIntake().Enable();
			Main::getIntake().SetSetpoint(m_point);
			m_finished = false;
		}

		virtual void Execute()
		{
			m_finished = Main::getIntake().OnTarget();
		}

		virtual bool IsFinished() { return m_finished; }
		virtual void End()
		{
			Main::getIntake().Disable();
		}

		virtual void Interrupted()
		{
			Main::getIntake().Disable();
		}

	private:
		bool  m_finished;
		float m_point;
};
