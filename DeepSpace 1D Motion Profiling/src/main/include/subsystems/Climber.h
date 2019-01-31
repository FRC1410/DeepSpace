#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>

#include "RobotMap.h"

class Climber : public frc::Subsystem {
  private:
    frc::DoubleSolenoid climber_front_solenoid{climber_front_port_start, climber_front_port_end};
    frc::DoubleSolenoid climber_back_solenoid{climber_back_port_start, climber_back_port_end};
    
  public:
    Climber();
    void InitDefaultCommand() override;
    void ExtendFront();
    void ExtendBack();
    void RetractFront();
    void RetractBack();
    void FrontOff();
    void BackOff();
};
