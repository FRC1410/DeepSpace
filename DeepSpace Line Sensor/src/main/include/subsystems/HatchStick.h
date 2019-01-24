#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>

#include "RobotMap.h"

class HatchStick : public frc::Subsystem {
  private:
    frc::DoubleSolenoid stick_solenoid {hatch_stick_port_start, hatch_stick_port_end};
  public:
    HatchStick();
    void InitDefaultCommand() override;
    void ExtendStick();
    void RetractStick();
    void StickOff();
};
