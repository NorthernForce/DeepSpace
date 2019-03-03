
#pragma once
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"

class Climber: public frc::Subsystem
{
public:
	Climber();
	void Lower();
	void Raise();
    void Stop();
    void DriveForward();
    void DriveBackward();
    void DriveStop();
    bool AtLowerLimit();
    bool AtUpperLimit();
    
private:
    std::shared_ptr<WPI_TalonSRX> m_masterTalonLifter;
	std::shared_ptr<WPI_TalonSRX> m_slaveTalonLifter;
    std::shared_ptr<WPI_TalonSRX> m_masterTalonWheels;



};
