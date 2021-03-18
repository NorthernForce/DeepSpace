#pragma once

#include "Commands/Command.h"
#include "../Main.h"

class DriveModeFlipped {};

class DriveModeRegular {};

template<class T>
class SetDriveMode: public Command
{
	public:
		SetDriveMode() :
			m_finished(false)
		{}

		virtual void Initialize()
		{
			m_finished = false;
		}

		virtual void Execute()
		{
			//std::cout << "Mode: " << mode << std::endl;

			specificExecute(T());
			/*
			switch(mode)
			{
				case R:
					Main::getDrive().FlipDrive(false);
					std::cout << "Set to regular." << std::endl;
					m_finished = true;
					break;
				case FLIPPED:
					Main::getDrive().FlipDrive(true);
					std::cout << "Set to flipped." << std::endl;
					m_finished = true;
					break;
			}
			*/
		}

		void specificExecute(const DriveModeRegular& mode)
		{
			Main::getDrive().FlipDrive(false);
			std::cout << "Set to regular." << std::endl;
			m_finished = true;
		}

		void specificExecute(const DriveModeFlipped& mode)
		{
			Main::getDrive().FlipDrive(true);
			std::cout << "Set to flipped." << std::endl;
			m_finished = true;
		}

		virtual bool IsFinished() { return m_finished; }
		virtual void End() {}
		virtual void Interrupted() {}

	private:
		bool m_finished;
};
