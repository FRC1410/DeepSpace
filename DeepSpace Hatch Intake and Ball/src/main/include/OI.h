#pragma once

#include <frc/Joystick.h>
#include <frc/Buttons/JoystickButton.h>

class OI {
  private:
	  frc::Joystick driver_controller{0};
    
  public:
    OI();
    frc::Joystick& GetJoystick();
	  double GetDriverAxis(int axis);
    double GetDriverButton(int button);
};
