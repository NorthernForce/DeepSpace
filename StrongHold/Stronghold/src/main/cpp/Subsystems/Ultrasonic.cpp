#include "UltrasonicSensor.h"
#include "RobotMap.h"


UltrasonicSensor::UltrasonicSensor(int analogChannel,  int serialChannel, int onChannel) :
	SubsystemWithCommand<void>("UltrasonicSensor"),
	kMinVoltage(0.5),
	kVoltageRange(5.0 - kMinVoltage),
	kMinDistance(3.0),
	kDistanceRange(60 - kMinDistance),
	m_distanceChannel(analogChannel),
	m_serialMode(serialChannel),
	m_sensorOn(onChannel)
{
	m_serialMode.Set(1);
	m_sensorOn.Set(1);
}

double UltrasonicSensor::GetRangeInInches() const
{
	return m_distanceChannel.GetVoltage() / (0.0098*12);
}
