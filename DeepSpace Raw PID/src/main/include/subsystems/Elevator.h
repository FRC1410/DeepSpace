/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

#include "RobotMap.h"

class Elevator : public frc::Subsystem {
  private:
    rev::CANSparkMax m_elevator_left{elevator_left_motor, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax m_elevator_right{elevator_right_motor, rev::CANSparkMax::MotorType::kBrushless};
    double current_velocity;

    rev::CANEncoder m_left_encoder = m_elevator_left.GetEncoder();
    rev::CANEncoder m_right_encoder = m_elevator_right.GetEncoder();
    double initial_left_revolutions, initial_right_revolutions;
    
    double PID_value, error, P, D;
    double I = 0;
    double previous_error = 0;

  public:
    Elevator();
    void InitDefaultCommand() override;

    void RunElevator(double speed);
    void Accelerate(double speed, double time_difference);
    void Goto(double target_location, double time_difference);
    double GetInput();

    void ResetEncoders();
    double GetLeftRevolutions();
    double GetRightRevolutions();
    double GetAverageRevolutions();
    double GetHeight();

    double GetPID(double target, double time_difference);
    void ResetIntegral(); 
    
    double GetLeftTemperature();
    double GetRightTemperature();
};