#pragma once

#include "Commands/Command.h"
#include "../Main.h"


class IntakeForward{};
class IntakeBackward{};
class IntakeStopped{};


template<class T>
class SetIntakeMode: public Command
{
	public:
		SetIntakeMode():
			m_finished(false)
		{
			Requires(&Main::getIntake());
		}

		virtual void Initialize()
		{
			m_finished = false;
		}

		virtual void Execute()
		{
			specificExecute(T());
		}

		void specificExecute(const IntakeForward& mode)
		{
			Main::getIntake().SetWheelForward();
			m_finished = true;
		}

		void specificExecute(const IntakeBackward& mode)
		{
			Main::getIntake().SetWheelBackward();
			m_finished = true;
		}

		void specificExecute(const IntakeStopped& mode)
		{
			Main::getIntake().SetWheelStopped();
			m_finished = true;
		}

		virtual bool IsFinished() { return false; }
		virtual void End() {}
		virtual void Interrupted() {}

	private:
		bool m_finished;
};
