#include "FRCXboxJoystick.h"
#include "Joystick.h"
#include <math.h>

/**
 * @brief This class constructs the instance
 * of the XBox Joystick. It automatically
 * calculates the deadband for the joysticks
 * on the controller.
 *
 * @author Arthur Lockman
 */
FRCXboxJoystick::FRCXboxJoystick(int port):
	Joystick(port),
     A(this, kXBoxButtonA),
     B(this, kXBoxButtonB),
     X(this, kXBoxButtonX),
     Y(this, kXBoxButtonY),
     Back(this, kXBoxButtonBack),
     Start(this, kXBoxButtonStart),
     LeftBumper(this, kXBoxButtonLeft),
     RightBumper(this, kXBoxButtonRight),
	 Deadband(0.0),
	 m_port(port)
{
 	CalculateDeadband();
}

float FRCXboxJoystick::GetX(JoystickHand hand)
{
	return DeadbandAdjust(Joystick::GetX(hand));
}

float FRCXboxJoystick::GetY(JoystickHand hand)
{
	return DeadbandAdjust(Joystick::GetY(hand));
}

void FRCXboxJoystick::CalculateDeadband()
{
    Deadband = 0.2; //0.025;
}

float FRCXboxJoystick::DeadbandAdjust(float val)
{
	float adjusted = val < Deadband && val > (-1 * Deadband)
	 ? 0.0
	 : (val-(fabs(val) / val * Deadband)) / (1 - Deadband);
	return adjusted;
}

float FRCXboxJoystick::GetLeftStickY()
{
	float value = Joystick::GetRawAxis(1.0); // was 2
	value = DeadbandAdjust(value);
	return -value;
}

float FRCXboxJoystick::GetLeftStickX()
{
	float value = Joystick::GetRawAxis(0.0); // was 1
	return -DeadbandAdjust(value);
}

float FRCXboxJoystick::GetRightStickY()
{
	float value = DeadbandAdjust(Joystick::GetRawAxis(5.0));
	return -value;
}

float FRCXboxJoystick::GetRightStickX()
{
	float value = DeadbandAdjust(Joystick::GetRawAxis(4.0));
	return -value;
}

float FRCXboxJoystick::GetRightTrigger()
{
	float value = Joystick::GetRawAxis(3.0);
	SmartDashboard::PutNumber(" Right Trigger", value);
	if (value > 0.5)
	{
		return value = 0.5;
	}

	if (value < -0.5)
	{
		return value = -0.5;
	}
	return value;
}

float FRCXboxJoystick::GetLeftTrigger()
{
	float value = Joystick::GetRawAxis(2.0);
	SmartDashboard::PutNumber(" Left Trigger", value);
	if (value > 0.5)
	{
		return value = 0.5;
	}

	if (value < -0.5)
	{
		return value = -0.5;
	}
	return value;
}

bool FRCXboxJoystick::GetAButton()
{
	return A.Get();
}

bool FRCXboxJoystick::GetBButton()
{
	return B.Get();
}

bool FRCXboxJoystick::GetXButton()
{
	return X.Get();
}

bool FRCXboxJoystick::GetYButton()
{
	return Y.Get();
}

bool FRCXboxJoystick::GetStartButton()
{
	return Start.Get();
}

bool FRCXboxJoystick::GetBackButton()
{
	return Back.Get();
}

bool FRCXboxJoystick::GetLeftBumper()
{
	return LeftBumper.Get();
}

bool FRCXboxJoystick::GetRightBumper()
{
	return RightBumper.Get();
}

