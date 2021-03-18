#pragma once

#include "Subsystems/SubsystemWithCommand.hpp"
#include "WPILib.h"
#include "AHRS.h"
#include "RobotMap.h"

/* The gyro we are using requires external libraries, namely the AHRS.h file.
 * This can be found at http://www.pdocs.kauailabs.com/navx-mxp/software/roborio-libraries/c/
 * In order to build this code, you will need to download the libraries and change some eclipse
 * settings. The instructions are on the website above. The AHRS class allows us to easily display
 * a variety of information from the gyro, including displacement, velocity, acceleration, angle,
 * and even quaternions. These values will be useful in both teleop (on the dashboard) and autonomous,
 * where the robot will be able to drive straight, for certain distances, at certain speeds, etc.
 */

class GyroSensor: public SubsystemWithCommand<void>
{
	public:

		GyroSensor();
		void init();
		void GetGyro();
		void Zero();
		float GetAngle();
		float GetDisplacement();

	private:
		AHRS *m_gyro;

};
