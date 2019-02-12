#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class HatchPickup : public frc::Subsystem {
  private:
    WPI_TalonSRX m_rotator{hatch_pickup_rotator};
    double error, P, D;
    double I = 0;
    double previous_error = 0;
    bool raised = true;
    
  public:
    HatchPickup();
    void InitDefaultCommand() override;
    void RotatePickup(double speed);
    void ResetEncoder();
    double GetPosition();
    double GetPID(double target, double time_difference);
    void ResetIntegral();
    void SetState(bool state);
    bool GetState();
};