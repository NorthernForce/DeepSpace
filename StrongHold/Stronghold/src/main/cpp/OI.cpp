#include "OI.h"
#include "Commands/SetDriveMode.hpp"
#include "Commands/SetIntakeMode.hpp"
#include "Commands/SetAxlePosition.hpp"
#include "Commands/SetAxleMotion.hpp"
#include "Commands/SetShooterMode.hpp"
#include "Commands/IntakeBall.hpp"
#include "Commands/ShootBall.hpp"
#include "Commands/ExpelBall.hpp"
#include "Commands/SetFlashlightMode.hpp"


OI::OI() :
	m_DriverStick(kDriverStickPort),
	m_ManipulatorStick(kManipulatorStickPort),
	m_XBoxManipulatorStick(kXBoxManipulatorPort) {}

void OI::init()
{
	m_DriverStick.RightBumper.WhenPressed<SetDriveMode<DriveModeFlipped> > ();
	m_DriverStick.LeftBumper.WhenPressed<SetDriveMode<DriveModeRegular> > ();

	m_DriverStick.A.WhenPressed<SetAxlePosition<UpPosition> > ();
	m_DriverStick.B.WhenPressed<SetAxlePosition<DownPosition> >();

	m_ManipulatorStick.Button4.ToggleWhenPressed<SetIntakeMode<IntakeForward> >();
	m_ManipulatorStick.Button4.ToggleWhenPressed<SetIntakeMode<IntakeStopped> >();

	m_ManipulatorStick.Button5.ToggleWhenPressed<SetIntakeMode<IntakeBackward> >();
	m_ManipulatorStick.Button5.ToggleWhenPressed<SetIntakeMode<IntakeStopped> >();

	m_ManipulatorStick.Button6.WhenPressed<IntakeBall<DownPosition> > (); // TEST
	m_ManipulatorStick.Button3.WhenPressed<ShootBall> ();
	m_ManipulatorStick.Trigger.WhenPressed<ExpelBall<OnTopPosition> > (); // was default

	m_ManipulatorStick.Button8.WhileHeld<SetAxleMotion<AxleMoveForward>> ();
	m_ManipulatorStick.Button8.WhenReleased<SetAxleMotion<AxleMoveStopped>> ();
	m_ManipulatorStick.Button9.WhileHeld<SetAxleMotion<AxleMoveBackward>> ();
	m_ManipulatorStick.Button9.WhenReleased<SetAxleMotion<AxleMoveStopped>> ();

	m_ManipulatorStick.Button7.WhenPressed<SetAxlePosition<DefaultPosition> >(); //intake
	m_ManipulatorStick.Button10.WhenPressed<SetAxlePosition<UpPosition> >();
	m_ManipulatorStick.Button11.WhenPressed<SetAxlePosition<DownPosition> >(); // was portcullis
	//m_ManipulatorStick.Button2.WhenPressed<SetAxlePosition<DownPosition> > (); //up
	//m_ManipulatorStick.Button11.WhenPressed<SetAxlePosition<PortcullisPosition> >();

	m_ManipulatorStick.Button2.ToggleWhenPressed<SetShooterMode<ShooterOn> >();
	m_ManipulatorStick.Button2.ToggleWhenPressed<SetShooterMode<ShooterOff> >();

	//m_ManipulatorStick.Button7.ToggleWhenPressed<SetFlashlightMode<FlashlightOn> >();
	//m_ManipulatorStick.Button7.ToggleWhenPressed<SetFlashlightMode<FlashlightOff> >();
}

FRCXboxJoystick& OI::GetDriverStick()
{
    return m_DriverStick;
}

Attack3Joystick& OI::GetManipulatorStick()
{
	return m_ManipulatorStick;
}

FRCXboxJoystick& OI::GetXBoxManipulatorStick()
{
	return m_XBoxManipulatorStick;
}
