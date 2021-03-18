#include "OpticalSensors.h"


OpticalSensors::OpticalSensors() :
	Subsystem("Optical Sensors"),
	m_opticalFront(8),
	m_opticalBack(9)
{}

float OpticalSensors::GetSensorFront()
{
	return m_opticalFront.Get();
}

float OpticalSensors::GetSensorBack()
{
	return m_opticalBack.Get();
}
