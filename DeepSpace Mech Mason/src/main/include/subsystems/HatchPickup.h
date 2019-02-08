#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class HatchPickup : public frc::Subsystem {
  private:
    WPI_TalonSRX m_rotator{hatch_pickup_rotator};
    double error, P, D;
    double I = 0;
    
  public:
    HatchPickup();
    void InitDefaultCommand() override;
    void RotatePickup(double speed);
    void ResetEncoder();
    double GetPosition();
    double GetPID(double previous_error, double target, double time_difference);
    void ResetIntegral();  
};