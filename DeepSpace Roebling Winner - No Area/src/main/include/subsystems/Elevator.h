/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <rev/CANSparkMax.h>

#include "RobotMap.h"

class Elevator : public frc::Subsystem {
  private:
    rev::CANSparkMax m_elevator_left{elevator_left_motor, rev::CANSparkMax::MotorType::kBrushless}, m_elevator_right{elevator_right_motor, rev::CANSparkMax::MotorType::kBrushless};
    double current_velocity;

    rev::CANEncoder m_left_encoder = m_elevator_left.GetEncoder();
    rev::CANEncoder m_right_encoder = m_elevator_right.GetEncoder();

    double initial_left_revolutions, initial_right_revolutions;
    bool encoder_failed;
    
    double PID_value, error, P, D;
    double I = 0;
    double previous_error = 0;

    nt::NetworkTableEntry shuffleboard_height = frc::Shuffleboard::GetTab("Mechanisms").Add("Elevator Height", elevator_min_height).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(1, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_target_height = frc::Shuffleboard::GetTab("Mechanisms").Add("Target Height", elevator_min_height).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(3, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_power = frc::Shuffleboard::GetTab("Mechanisms").Add("Elevator Power", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(1, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_left_temp = frc::Shuffleboard::GetTab("Mechanisms").Add("Left NEO Temp", 20).WithWidget(frc::BuiltInWidgets::kNumberBar).WithPosition(2, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_right_temp = frc::Shuffleboard::GetTab("Mechanisms").Add("Right NEO Temp", 20).WithWidget(frc::BuiltInWidgets::kNumberBar).WithPosition(3, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_average_revolutions = frc::Shuffleboard::GetTab("Mechanisms").Add("Average Revs", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(4, 2).WithSize(1, 1).GetEntry();

  public:
    Elevator();
    void InitDefaultCommand() override;

    void RunElevator(double speed);
    void Accelerate(double speed, double time_difference);
    void Goto(double target_location, double time_difference);

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