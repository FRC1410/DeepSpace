/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>

#include "RobotMap.h"
//#include "commands/BallClawWheelsRun.h"
//#include "commands/HatchWheelsRun.h"
//#include "commands/BallIntakeRun.h"

OI::OI() {
	/*ClawWheelsIn = new frc::JoystickButton(&driver_controller, ball_claw_outtake_button);
	ClawWheelsOut = new frc::JoystickButton(&driver_controller, ball_claw_intake_button);

	ClawWheelsIn->WhenPressed(new BallClawWheelsRun);
	ClawWheelsOut->WhenPressed(new BallClawWheelsRun);

	HatchWheelsIn = new frc::JoystickButton(&driver_controller, hatch_intake_button);
	HatchWheelsOut = new frc::JoystickButton(&driver_controller, hatch_outtake_button);

	HatchWheelsIn->WhenPressed(new HatchWheelsRun);
	HatchWheelsOut->WhenPressed(new HatchWheelsRun);*/
}

frc::Joystick& OI::GetJoystick() {
	return driver_controller;
}

double OI::GetDriverAxis(int axis){
	//This method returns a raw axis from driver_stick put through the deadband
	//The multiplier can speed up or slow down the driving of the robot
	return driver_controller.GetRawAxis(axis);
}

double OI::GetDriverButton(int button) {
	return driver_controller.GetRawButton(button);
}