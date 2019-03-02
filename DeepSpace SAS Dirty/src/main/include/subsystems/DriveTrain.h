/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <frc/drive/DifferentialDrive.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

#include "RobotMap.h"

class DriveTrain : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_front{left_front_drive};
    WPI_TalonSRX m_left_middle{left_middle_drive};
    WPI_TalonSRX m_left_back{left_back_drive};
    WPI_TalonSRX m_right_front{right_front_drive};
    WPI_TalonSRX m_right_middle{right_middle_drive};
    WPI_TalonSRX m_right_back{right_back_drive};

    frc::DifferentialDrive m_front{m_left_front, m_right_front};
    frc::DifferentialDrive m_middle{m_left_middle, m_right_middle};
    frc::DifferentialDrive m_back{m_left_back, m_right_back};

    AHRS * NavX = new AHRS(SPI::Port::kMXP);

    double average_distance;

    double distance_error, distance_P, distance_D;
    double distance_I = 0;
    double distance_previous_error = 0;

    double gyro_error, gyro_P, gyro_D;
    double gyro_I = 0;
    double gyro_previous_error = 0;

    double initial_velocity, initial_rotational_speed, tolerance, a, r1, r2, v1, v2, h, i1, i2, lower_skew, skew, upper_skew, lower_time, upper_time, dist, calc_time, calc_skew, calced_x, calced_z, hold;
    double stable_skew, stable_time, stable_r1, stable_r2, stable_v1, stable_h, stable_i1, stable_i2, stable_a, stable_c1, stable_c2, stable_c3;
    bool inverted_velocity, inverted_direction, stable_inverted_velocity, stable_inverted_direction;
    double c[24] = {};
    int counter, path_calcs, skew_counter;
    double distance_reference, angle_reference, distance, direction;
    double distance_PID, gyro_PID;

    double current_left_vel, current_right_vel;
    double left_vel_difference, right_vel_difference;

  public:
    DriveTrain();
    void InitDefaultCommand() override;
    void DisableSafety();
    void SetSpeed(double left, double right);
    void SetCurvedSpeed(double left, double right);
    double GetCurvedSpeed(double value);
    void Accelerate(double left, double right);
    void ResetEncoders();
    double GetDistance();
    void ResetNavX();
    double GetAngle();
    bool GetLeftSensor();
    bool GetMiddleSensor();
    bool GetRightSensor();
    double GetDistancePID(double target, double time_difference);
    void ResetDistanceIntegral(); 
    double GetGyroPID(double target, double time_difference);
    void ResetGyroIntegral();
    double GetRightDistance();
    double GetLeftDistance();
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
};