#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include <frc/commands/Command.h>

#include "RobotMap.h"

class OI {
  private:
	  frc::Joystick driver_controller{driver_port};
    frc::Joystick operator_controller{operator_port};

    double raw_magnitude;
    
  public:
    OI();
    double ApplyDeadzone(int controller, int axis, double userValue, double deadzone);
	  double GetDriverAxis(int axis);
    bool GetDriverButton(int button);
    int GetDriverDPad();
	  double GetOperatorAxis(int axis);
    bool GetOperatorButton(int button);
    int GetOperatorDPad();
    double GetAverageDriverInput();
    void SetDriverRumbleLeft(double value);
    void SetDriverRumbleRight(double value);
    void SetOperatorRumbleLeft(double value);
    void SetOperatorRumbleRight(double value);
};