#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Solenoid.h>

#include "RobotMap.h"

class HatchStick : public frc::Subsystem {
  private:
    frc::Solenoid stick_solenoid{stick_port};
  public:
    HatchStick();
    void InitDefaultCommand() override;
};
