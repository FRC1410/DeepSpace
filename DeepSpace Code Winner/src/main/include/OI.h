/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include <frc/commands/Command.h>

#include "RobotMap.h"

class OI {
  private:
	  frc::Joystick driver_controller{driver_port};
    frc::Joystick operator_controller{operator_port};
    frc::Joystick human_player_controller{human_player_port};

    double raw_magnitude;
    
  public:
    OI();
    double ApplyDeadzone(int controller, int axis, double userValue, double deadzone);
	  double GetDriverAxis(int axis);
    bool GetDriverButton(int button);
    int GetDriverDPad();
    double GetAverageDriverInput();
	  double GetOperatorAxis(int axis);
    bool GetOperatorButton(int button);
    int GetOperatorDPad();
    double GetHumanPlayerAxis(int axis);
    bool GetHumanPlayerButton(int button);
    void SetDriverRumbleLeft(double value);
    void SetDriverRumbleRight(double value);
    void SetOperatorRumbleLeft(double value);
    void SetOperatorRumbleRight(double value);
    double CalculateAntiAntiFriction();
};