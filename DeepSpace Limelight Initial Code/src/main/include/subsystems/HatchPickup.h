#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class HatchPickup : public frc::Subsystem {
  private:
    WPI_TalonSRX m_rotator{hatch_pickup_rotator};
    
  public:
    HatchPickup();
    void InitDefaultCommand() override;
    void RotatePickup(double speed);
};