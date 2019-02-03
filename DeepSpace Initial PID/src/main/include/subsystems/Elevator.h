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
    
    double error, P, D;
    double I = 0;
    double previous_speed;

    double initial_height;

  public:
    Elevator();
    void InitDefaultCommand() override;
    void RunElevator(double speed);
    void Accelerate(double speed);
    void ResetEncoders();
    double GetLeftRevolutions();
    double GetRightRevolutions();
    double GetAverageRevolutions();
    double GetHeight();
    void ResetHeight();
    double GetLeftTemperature();
    double GetRightTemperature();
    void SetAuto(bool auto_input);
    bool GetAuto();
    double GetPID(double previous_error, double target, double time_difference);
    void ResetIntegral(); 

  double current_vel;
  double vel_difference;
};