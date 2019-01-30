#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

#include "RobotMap.h"

class Elevator : public frc::Subsystem {
  private:
    rev::CANSparkMax m_elevator_left{elevator_left_motor, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax m_elevator_right{elevator_right_motor, rev::CANSparkMax::MotorType::kBrushless};

    rev::CANEncoder m_left_encoder = m_elevator_left.GetEncoder();
    rev::CANEncoder m_right_encoder = m_elevator_right.GetEncoder();

  public:
    Elevator();
    void InitDefaultCommand() override;
    void RunElevator(double speed);
    double GetLeftRevolutions();
    double GetRightRevolutions();
    double GetAverageRevolutions();
    double GetLeftTemperature();
    double GetRightTemperature();
    void SetAuto(bool auto_input);
    bool GetAuto();
};