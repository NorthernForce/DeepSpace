/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

namespace RobotMap {
    namespace WCDrive {
        const static int k_leftPrimary_id   = 1;
        const static int k_rightPrimary_id  = 2;
    }
    
    namespace BrushlessDrive {
        const static int k_leftPrimary_id = 1;
        const static int k_leftFollower_id = 3;

        const static int k_rightPrimary_id = 2;
        const static int k_rightFollower_id = 4;
    }

    namespace OI {
        const static int k_driverController_id = 0;
        const static int k_manipulatorController1_id = 1;
        const static int k_manipulatorController2_id = 2;
    }

    namespace CargoManipulator {
        const static int k_motor_id = 6;
    }
    namespace Elevator {
        const static int k_primary_id = 7;
        const static int k_follower1_id = 8;
        const static int k_follower2_id = 9;
        const static int k_follower3_id = 10;
        const static int k_solenoid_id = 2;
        const static double k_elevatorRaiseSpeed = 0.5;
        const static double k_elevatorLowerSpeed = -0.5;
        
        const static bool k_elevatorExtendedValue = 1;
        const static bool k_elevatorRetractedValue = 0;

    }

    namespace PCM {
        const static int k_pcm_id = 15;
    }

    namespace Claw {
        const static int k_clawSolenoid = 1;
        const static int k_raiseSolenoid = 2;

        const static bool k_clawOpenValue = 1;
        const static bool k_clawClosedValue = 0;
        const static bool k_clawRaisedValue = 1;
        const static bool k_clawLoweredValue = 0;

        constexpr static double k_timeToClose {0.4};
        constexpr static double k_timeToOpen {0.4};
        constexpr static double k_timeToRaise {0.4};
        constexpr static double k_timeToLower {0.4};

    }

}

