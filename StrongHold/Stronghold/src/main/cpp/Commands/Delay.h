#ifndef DELAY_H
#define DELAY_H

#include <WPILib.h>
#include <Timer.h>
#include "CommandBase.h"
#include "Commands/Command.h"


class Delay: public Timer
{
public:
	Delay(const float sec);

	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


private:
	Delay() ;
	double m_seconds;
};

#endif
