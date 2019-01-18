#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class HatchIntake : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_wheel{hatch_wheels_left};
    WPI_TalonSRX m_right_wheel{hatch_wheels_right};
    
  public:
    HatchIntake();
    void InitDefaultCommand() override;
    void RunWheels(double speed);
};