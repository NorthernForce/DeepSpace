#ifndef Ranger_H
#define Ranger_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Ultrasonic.h"


class Ranger: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Ranger();
	void InitDefaultCommand();
};

#endif
