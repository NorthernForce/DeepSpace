#pragma once

#include "WPILib.h"
#include "Commands/Command.h"
#include "OI.h"
#include "Subsystems/ArcadeDrive.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"
#include "Commands/Auto.h"
#include "Commands/StraightAuto.h"
#include "Commands/StraightAuto2.h"
#include "Subsystems/OpticalSensors.h"
#include "Subsystems/GyroSensor.h"
#include "Subsystems/UltrasonicSensor.h"
#include "Subsystems/Flashlight.h"
#include "Lib/ReadCommandFile.hpp"

class Main : public IterativeRobot
{
	public:
		Main();
		virtual ~Main();

		static Main& 				getRobot();
		static OI& 					getOI();
		static ArcadeDrive&			getDrive();
		static Intake&				getIntake();
		static Shooter&				getShooter();
		static OpticalSensors&		getOpticalSensors();
		static GyroSensor&			getGyroSensor();
	    static Flashlight&			getFlashlight();
	    static UltrasonicSensor&    getUltrasonicSensor();


	private:
		LiveWindow 		   *lw;
		Command*		   autocmd;//CommandGroup*      autocmd;
		SendableChooser    *m_chooser;
		OI				   m_oi;
		ArcadeDrive		   m_drive;
		Intake			   m_intake;
		Shooter			   m_shooter;
		OpticalSensors     m_optical;
		GyroSensor		   m_gyro;
		Flashlight  	   m_flashlight;
		UltrasonicSensor   m_ultrasonic;
		std::shared_ptr<CommandGroup> m_local;

		virtual void RobotInit();
		virtual void AutonomousInit();
		virtual void AutonomousPeriodic();
		virtual void TeleopInit();
		virtual void TeleopPeriodic();
		virtual void TestPeriodic();
};

