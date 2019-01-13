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

//DriveTrain
constexpr int left_front_drive = 1;
constexpr int left_back_drive = 2;
constexpr int right_front_drive = 3;
constexpr int right_back_drive = 4;

//Balls
constexpr int ball_claw_left = 5;
constexpr int ball_claw_right = 6;

constexpr int ball_claw_outtake_button = 5;
constexpr int ball_claw_intake_button = 6;

//Hatch
constexpr int hatch_wheels_left = 8;
constexpr int hatch_wheels_right = 9;

constexpr int hatch_intake_button = 1;
constexpr int hatch_outtake_button = 2;