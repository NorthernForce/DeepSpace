/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriverVision.h"

#include "RobotMap.h"

DriverVision::DriverVision() : Subsystem("ComputerVision") {
    m_driverCamera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("Driver Camera", RobotMap::DriverVision::k_driverCamera_id));
    m_manipulatorCamera = std::make_shared<cs::UsbCamera>(frc::CameraServer::GetInstance()->StartAutomaticCapture("Manipulator Camera", RobotMap::DriverVision::k_manipulatorCamera_id));
}
