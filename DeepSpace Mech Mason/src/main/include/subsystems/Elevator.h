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
    
    double initial_left_revolutions, initial_right_revolutions;
    double current_vel, vel_difference, PID_value;

    double error, P, D;
    double I = 0;
    double previous_error = 0;

    void CapValue(double value);

  public:
    Elevator();
    void InitDefaultCommand() override;
    void RunElevator(double speed, double PID);
    void Accelerate(double speed, double PID);
    void Goto(double target_location, double previous_height, double time_difference);
    double GetInput();
    double GetLeftRevolutions();
    double GetRightRevolutions();
    void ResetEncoders();
    double GetAverageRevolutions();
    double GetHeight();
    void ResetHeight();
    double GetPID(double target, double time_difference);
    void ResetIntegral(); 
    double GetLeftTemperature();
    double GetRightTemperature();
};