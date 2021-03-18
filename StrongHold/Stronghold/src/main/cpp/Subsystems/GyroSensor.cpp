#include "GyroSensor.h"


GyroSensor::GyroSensor() :
	SubsystemWithCommand<void>("Gyro Sensor"),
	m_gyro(0)
{
	m_gyro = new AHRS(SerialPort::kMXP);
}

void GyroSensor::init()
{
	Zero();
}

void GyroSensor::GetGyro()
{
	//SmartDashboard::PutBoolean( "Gyro_Connected",        m_gyro->IsConnected());
	//SmartDashboard::PutNumber(  "Gyro_Yaw",              m_gyro->GetYaw());
	//SmartDashboard::PutNumber(  "Gyro_Pitch",            m_gyro->GetPitch());
	//SmartDashboard::PutNumber(  "Gyro_Roll",             m_gyro->GetRoll());
	//SmartDashboard::PutNumber(  "Gyro_CompassHeading",   m_gyro->GetCompassHeading());
	//SmartDashboard::PutNumber(  "Gyro_Update_Count",     m_gyro->GetUpdateCount());
	//SmartDashboard::PutNumber(  "Gyro_Byte_Count",       m_gyro->GetByteCount());

	/* These functions are compatible w/the WPI Gyro Class */
	//SmartDashboard::PutNumber(  "Gyro_TotalYaw",         m_gyro->GetAngle());
	//SmartDashboard::PutNumber(  "Gyro_YawRateDPS",       m_gyro->GetRate());

	//SmartDashboard::PutNumber(  "Gyro_Accel_X",          m_gyro->GetWorldLinearAccelX());
	//SmartDashboard::PutNumber(  "Gyro_Accel_Y",          m_gyro->GetWorldLinearAccelY());
	//SmartDashboard::PutBoolean( "Gyro_IsMoving",         m_gyro->IsMoving());
	//SmartDashboard::PutNumber(  "Gyro_Temp_C",           m_gyro->GetTempC());
	//SmartDashboard::PutBoolean( "Gyro_IsCalibrating",    m_gyro->IsCalibrating());

	//SmartDashboard::PutNumber(  "Velocity_X",           m_gyro->GetVelocityX() );
	//SmartDashboard::PutNumber(  "Velocity_Y",           m_gyro->GetVelocityY() );
	//SmartDashboard::PutNumber(  "Displacement_X",       m_gyro->GetDisplacementX() );
	//SmartDashboard::PutNumber(  "Displacement_Y",       m_gyro->GetDisplacementY() );
}

void GyroSensor::Zero()
{
	//m_gyro->ZeroYaw();
}

float GyroSensor::GetAngle()
{
	return m_gyro->GetYaw();
}

float GyroSensor::GetDisplacement()
{
	return m_gyro->GetDisplacementX();
}


