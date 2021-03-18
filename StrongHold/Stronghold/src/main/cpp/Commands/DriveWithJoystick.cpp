#include "DriveWithJoystick.h"
#include "Main.h"
#include "../Lib/FRCXboxJoystick.h"

DriveWithJoystick::DriveWithJoystick()
{
	Requires(&Main::getDrive());
}

void DriveWithJoystick::Initialize()
{

}

void DriveWithJoystick::Execute()
{
	float x = Main::getOI().GetDriverStick().GetLeftStickY();
	float y = Main::getOI().GetDriverStick().GetRightStickX();
	bool z = true;

	Main::getDrive().DriveArcade(x, y, z);
}

bool DriveWithJoystick::IsFinished()
{
	return false;
}

void DriveWithJoystick::End()
{

}


void DriveWithJoystick::Interrupted()
{

}
