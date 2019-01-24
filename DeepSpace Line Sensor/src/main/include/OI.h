#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>
#include <frc/commands/Command.h>

#include "RobotMap.h"

class OI {
  private:
	  frc::Joystick driver_controller{driver_port};
    frc::Joystick operator_controller{operator_port};
    
    frc::JoystickButton * ClawWheelsOut;
	  frc::JoystickButton * ClawWheelsIn;
    frc::JoystickButton * HatchWheelsIn;
    frc::JoystickButton * HatchWheelsOut;
    frc::JoystickButton * BallRollerIn;
    frc::JoystickButton * BallRollerOut;

    frc::Command * drive_command;
    frc::Command * both_intakes;

    double raw_magnitude;
    

  public:
    OI();
    double ApplyDeadzone(int controller, int axis, double userValue, double deadzone);
	  double GetDriverAxis(int axis, double deadzone);
    bool GetDriverButton(int button);
	  double GetOperatorAxis(int axis, double deadzone);
    bool GetOperatorButton(int button);
    void SetDriverRumbleLeft(double value);
    void SetDriverRumbleRight(double value);
    void SetOperatorRumbleLeft(double value);
    void SetOperatorRumbleRight(double value);
};
