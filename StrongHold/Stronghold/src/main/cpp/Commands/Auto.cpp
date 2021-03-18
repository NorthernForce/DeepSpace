#include "./Auto.h"
#include "../Main.h"
#include "AutonomousDrive.hpp"
#include "ShootBall.hpp"
#include "SetShooterMode.hpp"



Auto::Auto()
{
//	AddParallel(new SetShooterMode<ShooterOn>());
//	AddSequential(new AutonomousDrive<DriveStraight>(6, 0.8, 3800, 0)); // was 5200, before that 4100
	AddSequential(new AutonomousDrive<RangeDrive>(6, 0.6, 4.30, 0)); // was 5200, before that 4100
//	AddSequential(new AutonomousDrive<DriveTurn>(2, 0.8, 0, 42.0));
//	AddSequential(new AutonomousDrive<DriveStraight>(3, 0.8, 1450, 0));
//	AddSequential(new AutonomousDrive<RangeDrive>(3, 0.6, 3.00, 0));
//	AddSequential(new ShootBall());
}



/*
 * Low bar start: go under, turn, shoot
 * Middle start: drive forward, turn, go under low bar, turn, shoot
 * Spy start: position, shoot
 */

//
