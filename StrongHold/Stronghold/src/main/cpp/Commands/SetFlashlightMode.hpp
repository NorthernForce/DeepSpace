
#pragma once

#include "Commands/Command.h"
#include "../Main.h"

class FlashlightOn{};
class FlashlightOff{};

template<class T>
class SetFlashlightMode: public Command
{
	public:
		SetFlashlightMode():
			m_finished(false)
		{
			Requires(&Main::getFlashlight());
		}

		virtual void Initialize()
		{
			m_finished = false;
		}

		virtual void Execute()
		{
			specificExecute(T());
		}

		void specificExecute(const FlashlightOn& mode)
		{
			Main::getFlashlight().TurnOn();
			m_finished = true;
		}

		void specificExecute(const FlashlightOff& mode)
		{
			Main::getFlashlight().TurnOff();
			m_finished = true;
		}

		virtual bool IsFinished() { return m_finished; }
		virtual void End() {}
		virtual void Interrupted() {}

	private:
		bool m_finished;
};




