#include "Main.h"
#include "Commands/AutonomousDrive.hpp"


Main::Main() : lw(0), autocmd(), m_chooser(), m_ultrasonic(1, 5, 1)
{
	m_chooser = new SendableChooser();
}

Main::~Main()
{
	delete autocmd;
}

Main& Main::getRobot()
{
	return static_cast<Main&>(RobotBase::getInstance());
}

OI& Main::getOI()
{
	return getRobot().m_oi;
}

ArcadeDrive& Main::getDrive()
{
	return getRobot().m_drive;
}

Intake& Main::getIntake()
{
	return getRobot().m_intake;
}

Shooter& Main::getShooter()
{
	return getRobot().m_shooter;
}

OpticalSensors& Main::getOpticalSensors()
{
	return getRobot().m_optical;
}

GyroSensor& Main::getGyroSensor()
{
	return getRobot().m_gyro;
}

Flashlight& Main::getFlashlight()
{
	return getRobot().m_flashlight;
}

UltrasonicSensor& Main::getUltrasonicSensor()
{
	return getRobot().m_ultrasonic;
}

void Main::RobotInit()
{
	m_oi.init();
	m_drive.init();
	m_intake.init();
	m_shooter.init();
	m_gyro.init();
	m_flashlight.init();

	m_chooser->AddDefault("Drive Straight", new StraightAuto());
	m_chooser->AddObject("Drive Straight 2", new StraightAuto2());
	m_chooser->AddObject("Low Bar Start", new Auto());
//	m_chooser->AddObject("Spy start, new Auto3());
	SmartDashboard::PutData("Autonomous modes", m_chooser);
	lw = LiveWindow::GetInstance();

	CameraServer::GetInstance()->SetQuality(50);
	CameraServer::GetInstance()->StartAutomaticCapture();
}

void Main::AutonomousInit()
{
	autocmd = (Command *) m_chooser->GetSelected();

	//std::string dir = "/home/auto/";
	//std::string fileName = SmartDashboard::GetString("Autonomous File", "Autonomous.txt");

	//std::cout << "About to read commands" << std::endl;
	//m_local = ACommandParser::ReadCommandFromFile(dir + fileName);
	//std::cout << "Read the commands" << std::endl;
	//autocmd = m_local.get();
	//std::cout << "About to start commands" << std::endl;
	autocmd->Start();
	//std::cout << "Started the commands" << std::endl;

}

void Main::AutonomousPeriodic()
{
	Scheduler::GetInstance()->Run();
}

void Main::TeleopInit()
{
}

void Main::TeleopPeriodic()
{
	Scheduler::GetInstance()->Run();
	//double voltage = getShooter().GetVoltage();
	//SmartDashboard::PutNumber("Voltage", voltage);
	//double speed = getShooter().GetCurrent();
	//SmartDashboard::PutNumber("Current", speed);
	double opticalOne = getOpticalSensors().GetSensorFront();
	double opticalTwo = getOpticalSensors().GetSensorBack();
	SmartDashboard::PutNumber("OpticalFront", opticalOne);
	SmartDashboard::PutNumber("OpticalBack", opticalTwo);

	double ultrasonic = getUltrasonicSensor().GetRangeInInches();
	SmartDashboard::PutNumber("Ultrasonic", ultrasonic);

	getGyroSensor().GetGyro();

	m_drive.PutEncoderValues();

	double intakeNumber = getIntake().GetPosition();

	//getIntake().SetInternalBackward(0.5);

	SmartDashboard::PutNumber("Intake Encoder", intakeNumber);
}

void Main::TestPeriodic()
{
	lw->Run();
}

START_ROBOT_CLASS(Main);

