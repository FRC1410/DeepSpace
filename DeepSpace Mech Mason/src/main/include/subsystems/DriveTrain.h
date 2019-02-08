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

    DigitalInput * left_tape_sensor = new DigitalInput(line_sensor_left);
    DigitalInput * middle_tape_sensor = new DigitalInput(line_sensor_middle);
    DigitalInput * right_tape_sensor = new DigitalInput(line_sensor_right);

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
    
  public:
    DriveTrain();
    void InitDefaultCommand() override;
    void SetSpeed(double left, double right);
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

    double current_left_vel;
    double current_right_vel;

    double left_vel_difference;
    double right_vel_difference;
};