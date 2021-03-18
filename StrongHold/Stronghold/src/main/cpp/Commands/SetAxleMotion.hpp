#pragma once

#include "Commands/Command.h"
#include "../Main.h"

class AxleMoveForward{};
class AxleMoveBackward{};
class AxleMoveStopped{};

template<class T>
class SetAxleMotion: public Command
{
	public:
		SetAxleMotion() :
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

		void specificExecute(const AxleMoveForward& mode)
		{
			Main::getIntake().SetAxleForward();
			std::cout << "Axle set forward." << std::endl;
			m_finished = true;
		}

		void specificExecute(const AxleMoveBackward& mode)
		{
			Main::getIntake().SetAxleBackward();
			std::cout << "Axle set backward." << std::endl;
			m_finished = true;
		}

		void specificExecute(const AxleMoveStopped& mode)
		{
			Main::getIntake().SetAxleStopped();
			std::cout << "Axle set stopped." << std::endl;
			m_finished = true;
		}


		virtual bool IsFinished() { return m_finished; }
		virtual void End() {}
		virtual void Interrupted() {}

	private:
		bool  m_finished;
};
