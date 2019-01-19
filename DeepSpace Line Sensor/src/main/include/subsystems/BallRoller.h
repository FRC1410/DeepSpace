#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class BallRoller : public frc::Subsystem {
  private:
    WPI_TalonSRX m_ball_roller{ball_roller};
  public:
    BallRoller();
    void InitDefaultCommand() override;
    void RunIntake(double speed);
};
