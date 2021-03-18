#include "Attack3Joystick.h"
#include <frc\Joystick.h>
#include <math.h>
/**
* @brief This method constructs the instance
* of the Attack 3 Joystick.
*
* @param port The port on which the joystick lives.
* @author Arthur Lockman
*/
Attack3Joystick::Attack3Joystick(int port):
	Joystick(port),
	Trigger(this, kAttackJoystickButtonTrigger),
	Button2(this, kAttackJoystickButton2),
	Button3(this, kAttackJoystickButton3),
	Button4(this, kAttackJoystickButton4),
	Button5(this, kAttackJoystickButton5),
	Button6(this, kAttackJoystickButton6),
	Button7(this, kAttackJoystickButton7),
	Button8(this, kAttackJoystickButton8),
	Button9(this, kAttackJoystickButton9),
	Button10(this, kAttackJoystickButton10),
	Button11(this, kAttackJoystickButton11),
	Button12(this, kAttackJoystickButton12)
	{}

float Attack3Joystick::GetStickX()
{
//@TODO: Check if this is the correct axis.
return Deadband(Joystick::GetRawAxis(1));
}

float Attack3Joystick::GetStickY()
{
//@TODO: Check if this is the correct axis.
return Deadband(Joystick::GetRawAxis(2));
}
float Attack3Joystick::Deadband(float input)
{
if (input < kDeadbandLimit && input > (kDeadbandLimit*(-1)))
return 0;
else
return (input-(fabs(input) / input * kDeadbandLimit)) / (1 - kDeadbandLimit);
}

float Attack3Joystick::GetPOT()
{
return Joystick::GetRawAxis(3);
}

bool Attack3Joystick::GetTrigger()
{
return Trigger.Get();
}

bool Attack3Joystick::GetButton2()
{
return Button2.Get();
}

bool Attack3Joystick::GetButton3()
{
return Button3.Get();
}

bool Attack3Joystick::GetButton4()
{
return Button4.Get();
}

bool Attack3Joystick::GetButton5()
{
return Button5.Get();
}

bool Attack3Joystick::GetButton6()
{
return Button6.Get();
}

bool Attack3Joystick::GetButton7()
{
return Button7.Get();
}

bool Attack3Joystick::GetButton8()
{
return Button8.Get();
}

bool Attack3Joystick::GetButton9()
{
return Button9.Get();
}

bool Attack3Joystick::GetButton10()
{
return Button10.Get();
}

bool Attack3Joystick::GetButton11()
{
return Button11.Get();
}

bool Attack3Joystick::GetButton12()
{
return Button12.Get();
}
