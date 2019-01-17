#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class BallClaw : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_wheel{ball_claw_left};
    WPI_TalonSRX m_right_wheel{ball_claw_right};

  public:
    BallClaw();
    void InitDefaultCommand() override;
    void RunWheels(double speed);
};
