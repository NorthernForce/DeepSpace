#pragma once

#include "Commands/Command.h"
#include "../Main.h"

class ShooterOn{};
class ShooterOff{};

template<class T>
class SetShooterMode: public Command
{
	public:
		SetShooterMode():
			m_finished(false)
		{
			Requires(&Main::getShooter());
		}

		virtual void Initialize()
		{
			m_finished = false;
		}

		virtual void Execute()
		{
			specificExecute(T());
		}

		void specificExecute(const ShooterOn& mode)
		{
			Main::getShooter().Forward();
			m_finished = true;
		}

		void specificExecute(const ShooterOff& mode)
		{
			Main::getShooter().Stopped();
			m_finished = true;
		}

		virtual bool IsFinished() { return m_finished; }
		virtual void End() {}
		virtual void Interrupted() {}

	private:
		bool m_finished;
};
