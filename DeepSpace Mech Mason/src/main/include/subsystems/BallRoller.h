#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>

#include "RobotMap.h"

class BallRoller : public frc::Subsystem {
  private:
    WPI_TalonSRX m_ball_roller{ball_roller};

    frc::DoubleSolenoid ball_solenoid{ball_roller_rotator_port_start, ball_roller_rotator_port_end};

    bool extended;
    
  public:
    BallRoller();
    void InitDefaultCommand() override;
    void RunIntake(double speed);
    void RollerDown();
    void RollerUp();
    void RollerOff();
    bool GetState();
    
};
