/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>

#include "RobotMap.h"

class OI {
  private:
	  frc::Joystick driver_controller{driver_port}, operator_controller{operator_port}, human_player_controller{human_player_port};

    double raw_magnitude;
    
  public:
    OI();
    double ApplyDeadzone(int controller, int axis, double userValue, double deadzone);

	  double GetDriverAxis(int axis);
    double GetAverageDriverInput();
    bool GetDriverButton(int button);
    int GetDriverDPad();
    void SetDriverRumble(double left, double right);

	  double GetOperatorAxis(int axis);
    bool GetOperatorButton(int button);
    int GetOperatorDPad();
    void SetOperatorRumble(double left, double right);

    double GetHumanPlayerAxis(int axis);
    bool GetHumanPlayerButton(int button);
};