/*
#ifndef READCOMMANDFILE_H

#include <memory>
#include <Commands/CommandGroup.h>

std::shared_ptr<CommandGroup> ReadCommandFromFile(const std::string& file_name);

#endif
*/

#pragma once

//#include "../Commands/AutonomousDrive.hpp"
//#include "../Commands/ShootBall.hpp"

#include <memory>
#include <string>

#include <Commands/CommandGroup.h>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

#include <vector>

// The AutoCommand classes
//

// Exception that is thrown by autonomous commands
struct AInvalidArgs{};

// Abstract base class that ensures all kinds of AAutoCommand implement the
// ToWpiCommand member function.
//
class AAutoCommand
{
   public:
      typedef std::vector<std::string> ArgumentList;
      virtual std::unique_ptr<Command> ToWpiCommand() const = 0;
      virtual ~AAutoCommand(){}
};

// An autonomous command that converts an argument list into a
// WPI library command that will propel the robot via direct driving
// commands.
//
// Required in the argument list:
//     duration: number of seconds (float)
//     speed: number of rotations (float)
//     angle: degree of drive (float)
//     distance: mm? (float)
//
class ADriveCommand : public AAutoCommand
{
   static const int kNumberOfArgs = 5;

   private:
      // Prevent default construction
      ADriveCommand() {}

   public:
      ADriveCommand(const ArgumentList& args);

      virtual std::unique_ptr<Command> ToWpiCommand() const;

   private:
      float m_duration;
      float m_speed;
      float m_distance;
      float m_angle;
};

// An autonomous command that converts an argument list into a
// WPI library command that will shoot a ball.
// commands.
//
// Required in the argument list:
//     None
//
class AShootCommand : public AAutoCommand
{
   private:
      AShootCommand() {}

   public:
      AShootCommand(const ArgumentList& args)
      {}

      virtual std::unique_ptr<Command> ToWpiCommand() const;

};

// An autonomous command that converts an argument list into a
// WPI library command that will propel the robot via vector driving
// commands.
//
// Required in the argument list:
//     type: a (relative to robot axis (normal)) or r (relative to the field - not yet implemented)
//     duration: number of seconds (float)
//     speed: number of rotations (float)
//     angle: degree of drive (float)
//     distance: mm? (float)
//
class AVectorDriveCommand : public AAutoCommand
{
   static const int kNumberOfArgs = 5;

   private:
      AVectorDriveCommand() {}

   public:
      AVectorDriveCommand(const ArgumentList& args);

      virtual std::unique_ptr<Command> ToWpiCommand() const;
   private:
      char  m_type;
      float m_duration;
      float m_speed;
      float m_distance;
      float m_angle;
};

// An autonomous command that converts an argument list into a
// WPI library command that will align the robot based on sensor input.
//
// NOTE: This in not yet implemented.
//
class AAimCommand : public AAutoCommand
{
   private:
      AAimCommand() {}

   public:
      AAimCommand(const ArgumentList& args)
      {}

      virtual std::unique_ptr<Command> ToWpiCommand() const;

};

// A specialized kind of CommandGroup that persists commands and
// manages the addition of these commands to the CommandGroup for
// sequential or parallel execution.
//
class CommandGroupFromFile : public CommandGroup
{
   public:
      void AppendCommand(std::unique_ptr<Command>&& cmd)
      {
         AddSequential(cmd.get());
         m_commands.emplace_back(std::move(cmd));
      }

      void ParallelCommand(std::unique_ptr<Command>&& cmd)
      {
         AddParallel(cmd.get());
      }

   private:
      std::vector<std::unique_ptr<Command>> m_commands;
};

// A Helper class that encapsulates the parsing of an autonomous mode command file.
// The command file has the following structure:
//
// # args: time(sec), speed (-1, 1), distance (mm), angle(degrees)
//
// d 5 0.8 4100 0
// d 2 0.8 0 33.5
// d 3 0.8 600 0
// s
//
// Lines starting with a '#' are comments and are ignored by the parser. The
// parser currently supports 4 kinds of commands:
//    Vector Drive
//    Drive
//    Shoot
//    Aim with reflective tape using camera - incomplete
//
// Command type arguments
// ----------------------
// Vector Drive
//     type: a (relative to robot axis (normal)) or r (relative to the field - not yet implemented)
//     duration: number of seconds (float)
//     speed: number of rotations (float)
//     angle: degree of drive (float)
//     distance: mm? (float)
//
// Drive
//     duration: number of seconds (float)
//     speed: number of rotations (float)
//     angle: degree of drive (float)
//     distance: mm? (float)
//
// Shoot
//     No arguments
//
// Aim with reflective tape
//     No arguments
//
class ACommandParser
{
   public:
      // Reads lines from the command input file and returns a
      // std::shared_ptr<CommandGroup>
      //
      // @param const std::string&  - Fully qualified file name (includes path information)
      // @returns {std::shared_ptr<CommandGroup>}
      static std::shared_ptr<CommandGroup> ReadCommandFromFile(const std::string& fileName)
      {
         std::ifstream file;
         file.open(fileName);
         if (!file.fail())
         {
            //std::stringstream ss;
            //ss << file.rdbuf();
            //std::string myString = ss.str();

            //SmartDashboard::PutString("Autonomous", myString);
            return LoadCommandGroupFromFile(file);
         }

         std::clog << "Auto command file failed to open:" << fileName << std::endl;
         return nullptr;
      }

   private:
      // Reads lines from the command input stream and returns a
      // std::shared_ptr<CommandGroup>
      //
      // @param std::istream& is - Input stream from which commands are read
      // @returns {std::shared_ptr<CommandGroup>}
      static std::shared_ptr<CommandGroup> LoadCommandGroupFromFile(std::istream& is)
      {
         auto cmdGroup = std::make_shared<CommandGroupFromFile>();
         std::string line;
         while (std::getline(is, line))
         {
            if (auto cmd = GetCommand(line))
            {
               cmdGroup->AppendCommand(std::move(cmd));
               std::cout << "Line: " << line << std::endl;
            }
         }

         return cmdGroup;
      }

   private:
      // Splits a string s into a vector of parts where each part is delimited
      // by the character delim.
      //
      // @param std::string s - String to parse
      // @param char delim - Delimiting character
      // @returns {std::vector<std::string>}
      static std::vector<std::string> split(const std::string &s, char delim)
      {
         std::vector<std::string> tokens;
         std::stringstream ss(s);
         std::string item;
         while (std::getline(ss, item, delim))
         {
            tokens.push_back(item);
         }
         return tokens;
      }

      // Parses the raw line of command characters into a unique_ptr<Command>.
      //
      // @param std::string line - A line from the command file
      // @returns { std::unique_ptr<Command>}
      static std::unique_ptr<Command> GetCommand(const std::string& line)
      {
         if (line.empty())
         {
            return nullptr;
         }

         // Use of an ArgumentList takes a bit more storage than manipulating the
         // raw istream buffer but makes the code much easier to follow and is
         // less prone to pointer based segfaults.
         AAutoCommand::ArgumentList tokens = split(line, ' ');
         char cmd = tokens[0][0];
         switch (cmd)
         {
            case 'v': // Vector Drive
            return AVectorDriveCommand(tokens).ToWpiCommand();

            case 'd': // Drive
            return ADriveCommand(tokens).ToWpiCommand();

            case 's': // Shoot
            return AShootCommand(tokens).ToWpiCommand();

            case 'a': // Aim with reflective tape using camera - incomplete
            return AAimCommand(tokens).ToWpiCommand();

            case '#': // Comment
            break;

            default:
            std::clog << "Invalid command line:" << line << std::endl;
         }

         return nullptr;
      }
};

