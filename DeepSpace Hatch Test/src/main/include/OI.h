/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>

class OI {
 public:
  OI();
  frc::Joystick& GetJoystick();
	double GetDriverAxis(int axis);
  double GetDriverButton(int button);

private:
	frc::Joystick driver_controller{0};

  frc::JoystickButton * ClawWheelsOut;
	frc::JoystickButton * ClawWheelsIn;
  frc::JoystickButton * HatchWheelsIn;
	frc::JoystickButton * HatchWheelsOut;
  frc::JoystickButton * BallRoller;
};
