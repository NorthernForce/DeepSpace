/*

#include "ReadCommandFile.hpp"
#include "Commands/ShootBall.hpp"
#include "Commands/AutonomousDrive.hpp"


#include "Main.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

namespace
{
class CommandGroupFromFile : public CommandGroup
{
public:
	void AppendCommand(std::unique_ptr<Command>&& cmd)
	{
		AddSequential(cmd.get());
		commands.emplace_back(std::move(cmd));
	}

	void ParallelCommand(std::unique_ptr<Command>&& cmd)
	{
		AddParallel(cmd.get());
	}

private:
	std::vector<std::unique_ptr<Command>> commands;
};

void ReportBadFileName(const std::string& file_name)
{
	std::clog << "Auto command file failed to open:" << file_name << std::endl;
}

void ReportBadCommand(const std::string& command)
{
	std::clog << "Invalid command line:" << command << std::endl;
}

std::unique_ptr<Command> BuildVectorDriveCommand(char* s)
{
	++s;

	float duration;// = std::strtof(++s, &s);
	float speed;// = std::strtof(++s, &s);
	float distance;// = std::strtof(++s, &s);
	float angle;// = std::strtof(++s, &s);

	switch(*s)
	{
		case 'r': // relative to robot axis (normal)
			duration = std::strtof(++s, &s);
			speed = std::strtof(++s, &s);
			angle = std::strtof(++s, &s);
			distance = std::strtof(++s, &s);
			return std::unique_ptr<Command>(new AutonomousDrive<VectorDriveToRobot>(duration, speed, distance, angle));

		case 'a': // relative to the field - not yet implemented - need to include gyro
			duration = std::strtof(++s, &s);
			speed = std::strtof(++s, &s);
			angle = std::strtof(++s, &s);
			distance = std::strtof(++s, &s);
			return std::unique_ptr<Command>(new AutonomousDrive<VectorDriveToField>(duration, speed, distance, angle));

	}

	return nullptr;
}

std::unique_ptr<Command> BuildDriveCommand(char* s)
{
	const float duration = std::strtof(++s, &s);
	const float speed = std::strtof(++s, &s);
	const float distance = std::strtof(++s, &s);
	const float angle = std::strtof(++s, &s);
	return std::unique_ptr<Command>(new AutonomousDrive<DriveStraight>(duration, speed, distance, angle));

}

std::unique_ptr<Command> BuildShootCommand(char*)
{
	return std::unique_ptr<Command>(new ShootBall());
}

std::unique_ptr<Command> BuildAimCommand(char*)
{
	return nullptr;
	//return std::unique_ptr<Command>(new Align());
}

std::unique_ptr<Command> GetCommand(const std::string& line)
{
	if(line.empty())
	{
		return nullptr;
	}

	char* s = const_cast<char*>(line.c_str());
	switch(std::tolower(*s++))
	{
	case 'v': // Vector Drive
		return BuildVectorDriveCommand(s);

	case 'd': // Drive
		return BuildDriveCommand(s);

	case 's': // Shoot
		return BuildShootCommand(s);

	case 'a': // Aim with reflective tape using camera - incomplete
		return BuildAimCommand(s);

	case '#': // Comment
		break;

	default:
		ReportBadCommand(line);
	}

	return nullptr;
}

std::shared_ptr<CommandGroup> LoadCommandGroupFromFile(std::istream& is)
{
	auto cmd_group = std::make_shared<CommandGroupFromFile>();
	std::string line;
	while (std::getline(is, line))
	{
		if(auto cmd = GetCommand(line))
			cmd_group->AppendCommand(std::move(cmd));
	}

	return cmd_group;
}

}

std::shared_ptr<CommandGroup> ReadCommandFromFile(const std::string& file_name)
{
	std::ifstream file;
	file.open(file_name);
	if (!file.fail())
	{
		std::stringstream ss;
		ss << file;
		std::string myString = ss.str();

		SmartDashboard::PutString("Autonomous", myString);
		return nullptr;//LoadCommandGroupFromFile(file);
	}

	ReportBadFileName(file_name);
	return nullptr;
}

*/
#include "ReadCommandFile.hpp"
#include "../Commands/AutonomousDrive.hpp"
#include "../Commands/AutoShoot.hpp"

ADriveCommand::ADriveCommand(const ArgumentList& args)
{
	// Verify that there are the proper number of arguments
	if (kNumberOfArgs != args.size())
		throw AInvalidArgs();

	 int i = 1;
	m_duration = std::stof(args[i++]);
	m_speed = std::stof(args[i++]);
	m_distance = std::stof(args[i++]);
	m_angle = std::stof(args[i++]);
}

std::unique_ptr<Command> ADriveCommand::ToWpiCommand() const
{
	if(m_angle == 0.0)
	{
		return std::unique_ptr<Command>(
		new AutonomousDrive<DriveStraight>(m_duration, m_speed, m_distance, m_angle));
	}

	else
	{
		return std::unique_ptr<Command>(
		new AutonomousDrive<DriveTurn>(m_duration, m_speed, m_distance, m_angle));
	}
}

std::unique_ptr<Command> AShootCommand::ToWpiCommand() const
{
	return std::unique_ptr<Command>(new AutoShoot());
}

AVectorDriveCommand::AVectorDriveCommand(const ArgumentList& args)
{
	// Verify that there are the proper number of arguments
	if (kNumberOfArgs != args.size())
		throw AInvalidArgs();

	int i = 1;

	m_type = args[1][0];
	m_duration = std::stof(args[i++]);
	m_speed = std::stof(args[i++]);
	m_angle = std::stof(args[i++]);
	m_distance = std::stof(args[i++]);
}

std::unique_ptr<Command> AVectorDriveCommand::ToWpiCommand() const
{
	switch (m_type)
	{
		case 'r': // relative to robot axis (normal)
		return std::unique_ptr<Command>(new AutonomousDrive<VectorDriveToRobot>(m_duration, m_speed, m_distance, m_angle));

		case 'a': // relative to the field - not yet implemented - need to include gyro
		return std::unique_ptr<Command>(new AutonomousDrive<VectorDriveToField>(m_duration, m_speed, m_distance, m_angle));
	}

	return nullptr;
}

std::unique_ptr<Command> AAimCommand::ToWpiCommand() const
{
   return nullptr; //std::unique_ptr<Command>(new Align());
}


