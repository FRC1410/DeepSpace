/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/WPILib.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

#include "RobotMap.h"

class DriveTrain : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_front{left_front_drive}, m_left_middle{left_middle_drive}, m_left_back{left_back_drive};
    WPI_TalonSRX m_right_front{right_front_drive}, m_right_middle{right_middle_drive}, m_right_back{right_back_drive};

    frc::SpeedControllerGroup m_left{m_left_front, m_left_middle, m_left_back}, m_right{m_right_front, m_right_middle, m_right_back};
    frc::DifferentialDrive m_tank{m_left, m_right};

    double left_velocity, right_velocity;
    double initial_left_position, initial_right_position;
    double x_position, z_position;
    
    AHRS * NavX = new AHRS(SPI::Port::kMXP);
    double initial_angle = 0;

    double distance_error, distance_P, distance_D;
    double distance_I = 0;
    double distance_previous_error = 0;
    double input_distance_kP = drivetrain_distance_kP;
    double input_distance_kI = drivetrain_distance_kI;
    double input_distance_kD = drivetrain_distance_kD;

    double gyro_error, gyro_P, gyro_D;
    double gyro_I = 0;
    double gyro_previous_error = 0;
    double input_gyro_kP = drivetrain_gyro_kP;
    double input_gyro_kI = drivetrain_gyro_kI;
    double input_gyro_kD = drivetrain_gyro_kD;

    double input_limelight_kP = limelight_distance_kP;
    double input_limelight_kI = limelight_distance_kI;
    double input_limelight_kD = limelight_distance_kD;

    std::string previous_PID_mode = "m_gyro";
    
    double c[24];
    int counter, path_calcs, skew_counter;
    double initial_velocity, initial_rotational_speed, tolerance;
    double a, r1, r2, v1, v2, h, i1, i2;
    double lower_skew, skew, upper_skew, lower_time, upper_time;
    double dist, hold, calc_time, calc_skew, calced_x, calced_z;
    double stable_skew, stable_time, stable_r1, stable_r2, stable_v1, stable_a;
    double stable_h, stable_i1, stable_i2, stable_c1, stable_c2, stable_c3;
    bool inverted_velocity, inverted_direction, stable_inverted_velocity, stable_inverted_direction;
    double distance_reference, angle_reference, distance, direction;
    double distance_PID, gyro_PID;

    frc::SendableChooser<std::string> m_chooser;
    nt::NetworkTableEntry shuffleboard_inverted_driving = frc::Shuffleboard::GetTab("Drivers").Add("Inverted Driving", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(1, 1).WithSize(1, 2).GetEntry();

    nt::NetworkTableEntry shuffleboard_x = frc::Shuffleboard::GetTab("Drivetrain").Add("X", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_z = frc::Shuffleboard::GetTab("Drivetrain").Add("Z", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(0, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_left_power = frc::Shuffleboard::GetTab("Drivetrain").Add("Left Power", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(1, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_right_power = frc::Shuffleboard::GetTab("Drivetrain").Add("Right Power", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(3, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_gyro = frc::Shuffleboard::GetTab("Drivetrain").Add("Gyro", 0).WithWidget(frc::BuiltInWidgets::kGyro).WithPosition(5, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_average_distance = frc::Shuffleboard::GetTab("Drivetrain").Add("Average Distance", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(1, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_left_distance = frc::Shuffleboard::GetTab("Drivetrain").Add("Left Distance", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_right_distance = frc::Shuffleboard::GetTab("Drivetrain").Add("Right Distance", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(3, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_speed = frc::Shuffleboard::GetTab("Drivetrain").Add("Speed", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(4, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_rotational_speed = frc::Shuffleboard::GetTab("Drivetrain").Add("Rotational Speed", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(5, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_inverted = frc::Shuffleboard::GetTab("Drivetrain").Add("Inverted", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(6, 2).WithSize(1, 1).GetEntry();
    
    nt::NetworkTableEntry shuffleboard_P_input = frc::Shuffleboard::GetTab("Auto").Add("P Input", 0).WithWidget(frc::BuiltInWidgets::kNumberSlider).WithPosition(0, 0).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_I_input = frc::Shuffleboard::GetTab("Auto").Add("I Input", 0).WithWidget(BuiltInWidgets::kNumberSlider).WithPosition(0, 1).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_D_input = frc::Shuffleboard::GetTab("Auto").Add("D Input", 0).WithWidget(frc::BuiltInWidgets::kNumberSlider).WithPosition(0, 2).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_P = frc::Shuffleboard::GetTab("Auto").Add("P", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_I = frc::Shuffleboard::GetTab("Auto").Add("I", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_D = frc::Shuffleboard::GetTab("Auto").Add("D", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_angle_error = frc::Shuffleboard::GetTab("Auto").Add("Angle Error", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(3, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_distance_error = frc::Shuffleboard::GetTab("Auto").Add("Distance Error", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(5, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_current_time = frc::Shuffleboard::GetTab("Auto").Add("Current Time", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(4, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_time = frc::Shuffleboard::GetTab("Auto").Add("Time", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(5, 2).WithSize(1, 1).GetEntry();

  public:
    DriveTrain();
    void InitDefaultCommand() override;

    void SetSpeed(double left, double right);
    void SetCurvedSpeed(double left, double right);
    double GetCurvedSpeed(double value);
    
    double ApplyAcceleration(double current_speed, double target_speed, double time_difference);
    void Accelerate(double left, double right, double time_difference);
    void CurvedAccelerate(double left, double right, double time_difference);

    void ResetEncoders();
    double GetLeftDistance();
    double GetRightDistance();
    double GetDistance();

    void ResetNavX(double start);
    double GetAngle();

    void SetX(double value);
    void SetZ(double value);
    void IncrementX(double increment);
    void IncrementZ(double increment);
    double GetX();
    double GetZ();

    double GetDistancePID(double target, double time_difference);
    void ResetDistanceIntegral();

    double GetGyroPID(double target, double time_difference);
    void ResetGyroIntegral();

    void SetPIDConstants();

    double FresnelSineCalc(double input);
    double FresnelCosineCalc(double input);
    double CalcPathX(double skew, double time);
    double CalcPathZ(double skew, double time);

    void SetVars(double time);
    double CalcSkew(double time, double aspect);
    bool CalculateRawPath(double target_x, double target_z, double angle, double final_velocity, double final_rotational_speed);
    bool CalculatePath(double x_displacement, double z_displacement, double angle, double final_velocity, double final_rotational_speed);

    void FollowPath(double time, double time_difference);
    double GetPathTime();
    void ResetTime();

    void DisplayData(double speed, double rotational_speed, bool inverted);
};