/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <frc/Spark.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <AHRS.h>

#include "RobotMap.h"

class MacroSuperstructure : public frc::Subsystem {
  private:
    bool running_auto, FMS_auto;
    int inverted_auto;

    int profile = 0;
    bool reset = false;

    frc::Compressor m_compressor;
    AnalogInput pressure_input{pressure_sensor};

    frc::Spark left_LEDs{left_LED_controller_port};
    frc::Spark right_LEDs{right_LED_controller_port};

    frc::SpeedControllerGroup LEDs{left_LEDs, right_LEDs};

    nt::NetworkTableEntry shuffleboard_warnings = frc::Shuffleboard::GetTab("Drivers").Add("Warnings", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(2, 1).WithSize(3, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_hatch = frc::Shuffleboard::GetTab("Drivers").Add("Hatch", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_cargo = frc::Shuffleboard::GetTab("Drivers").Add("Cargo", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(0, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_voltage = frc::Shuffleboard::GetTab("Drivers").Add("Voltage", 0).WithWidget(frc::BuiltInWidgets::kVoltageView).WithPosition(1, 0).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_time = frc::Shuffleboard::GetTab("Drivers").Add("Time", 0).WithWidget(frc::BuiltInWidgets::kNumberBar).WithPosition(3, 0).WithSize(2, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_pressure = frc::Shuffleboard::GetTab("Drivers").Add("Pressure", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(5, 1).WithSize(2, 2).GetEntry();
    nt::NetworkTableEntry shuffleboard_LEDs = frc::Shuffleboard::GetTab("Mechanisms").Add("LED Color", 0).WithWidget(frc::BuiltInWidgets::kNumberBar).WithPosition(0, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_compressor = frc::Shuffleboard::GetTab("Mechanisms").Add("Compressor", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(5, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_stage = frc::Shuffleboard::GetTab("Auto").Add("Stage", 0).WithWidget(frc::BuiltInWidgets::kTextView).WithPosition(6, 2).WithSize(1, 1).GetEntry();
   
  public:
    MacroSuperstructure();
    void InitDefaultCommand() override;

    void SetAuto(bool auto_input);
    bool GetAuto();

    void SetFMSAuto(bool auto_input);
    bool GetFMSAuto();
    
    void SetInvertedAuto(bool input);
    int GetInvertedAuto();

    void SetProfile(int direction);
    int GetProfile();
    bool GetReset();

    void SetCompressor(bool state);
    double GetPressure();
    double GetBatteryVoltage();

    void SetLEDs(double value);
    void SetWarnings(bool warnings, double time);
    void SetStage(double stage);

    double CapValue(double value, double cap);
    double GetDirection(double x, double y);
};