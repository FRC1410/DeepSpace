#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class BallIntake : public frc::Subsystem {
  private:
    WPI_TalonSRX m_ball_intake{ball_intake};
  public:
    BallIntake();
    void InitDefaultCommand() override;
    void RunIntake(double speed);
};
