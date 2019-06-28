/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include "RobotMap.h"

class Limelight : public frc::Subsystem {
  private:
    std::shared_ptr<NetworkTable> limelight_table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    
    int pipeline = 0;
    bool target_found;

    double angle_error, angle_P, angle_D;
    double angle_I = 0;
    double angle_previous_error = 0;
    double input_angle_kP = limelight_angle_kP;
    double input_angle_kI = limelight_angle_kI;
    double input_angle_kD = limelight_angle_kD;

    double area_error, area_P, area_D;
    double area_I = 0;
    double area_previous_error = 0;
    double input_area_kP = limelight_area_kP;
    double input_area_kI = limelight_area_kI;
    double input_area_kD = limelight_area_kD;
    
    double distance_error, distance_P, distance_D;
    double distance_I = 0;
    double distance_previous_error = 0;
    double input_distance_kP = limelight_distance_kP;
    double input_distance_kI = limelight_distance_kI;
    double input_distance_kD = limelight_distance_kD;

    bool was_area = false;
    
    nt::NetworkTableEntry shuffleboard_P_input = frc::Shuffleboard::GetTab("Limelight").Add("P Input", input_angle_kP).WithWidget(frc::BuiltInWidgets::kNumberSlider).WithPosition(0, 0).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_I_input = frc::Shuffleboard::GetTab("Limelight").Add("I Input", input_angle_kI).WithWidget(frc::BuiltInWidgets::kNumberSlider).WithPosition(0, 1).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_D_input = frc::Shuffleboard::GetTab("Limelight").Add("D Input", input_angle_kD).WithWidget(frc::BuiltInWidgets::kNumberSlider).WithPosition(0, 2).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_P = frc::Shuffleboard::GetTab("Limelight").Add("P", input_angle_kP).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_I = frc::Shuffleboard::GetTab("Limelight").Add("I", input_angle_kI).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_D = frc::Shuffleboard::GetTab("Limelight").Add("D", input_angle_kD).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(2, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_error = frc::Shuffleboard::GetTab("Limelight").Add("Error", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(3, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_PID_value = frc::Shuffleboard::GetTab("Limelight").Add("PID Value", 0).WithWidget(frc::BuiltInWidgets::kGraph).WithPosition(5, 0).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_area_PID = frc::Shuffleboard::GetTab("Limelight").Add("Area PID", false).WithWidget(frc::BuiltInWidgets::kToggleButton).WithPosition(3, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_tx = frc::Shuffleboard::GetTab("Limelight").Add("Tx", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(4, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_ta = frc::Shuffleboard::GetTab("Limelight").Add("Ta", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(5, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_tv = frc::Shuffleboard::GetTab("Limelight").Add("Tv", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(6, 2).WithSize(1, 1).GetEntry();

    nt::NetworkTableEntry shuffleboard_vision = frc::Shuffleboard::GetTab("Drivers").Add("Vision Target", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(5, 0).WithSize(1, 1).GetEntry();

  public:
    Limelight();
    void InitDefaultCommand() override;

    bool GetTarget();
    double GetTargetX();
    double GetTargetArea();

    void SetPipeline(int pipeline);
    int GetPipeline();
    void SetTargetFound(bool target);
    bool GetTargetFound();

    double GetAnglePID(double target, double time_difference);
    double ResetAngleIntegral();

    double GetAreaPID(double target, double time_difference);
    double ResetAreaIntegral();

    double GetDistancePID(double target, double time_difference);
    double ResetDistanceIntegral();

    void SetPIDConstants();
    void SetDistancePIDConstants(double kP, double kI, double kD);
};