/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Spark.h>
#include <frc/WPILib.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <AHRS.h>

#include "RobotMap.h"

class MacroSuperstructure : public frc::Subsystem {
  private:
    /*nt::NetworkTableEntry shuffleboard_hatch = frc::Shuffleboard::GetTab("Drivers").Add("Hatch", false).WithWidget("Boolean Box").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_cargo = frc::Shuffleboard::GetTab("Drivers").Add("Cargo", false).WithWidget("Boolean Box").WithPosition(0, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_climber = frc::Shuffleboard::GetTab("Drivers").Add("Climber", false).WithWidget("Boolean Box").WithPosition(0, 2).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_voltage = frc::Shuffleboard::GetTab("Drivers").Add("Voltage", 0).WithWidget("Voltage View").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_time = frc::Shuffleboard::GetTab("Drivers").Add("Time", 0).WithWidget("Number Bar").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_warnings = frc::Shuffleboard::GetTab("Drivers").Add("Warnings", 0).WithWidget("Boolean Box").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_auto_inverter = frc::Shuffleboard::GetTab("Drivers").Add("Auto Inverter", 0).WithWidget("Toggle Button").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_pressure = frc::Shuffleboard::GetTab("Drivers").Add("Pressure", 0).WithWidget("Toggle Button").WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_pressure = frc::Shuffleboard::GetTab("Drivers").Add("", 0).WithWidget("Toggle Button").WithPosition(0, 0).WithSize(1, 1).GetEntry();*/

    bool running_auto;
    bool inverted_auto;
    bool FMS_auto;

    int handoff_stage;
    bool vision_targeting = false;

    int profile = 0;
    bool reset = false;

    bool encoder_failed;

    frc::Compressor m_compressor;
    AnalogInput pressure_input{pressure_sensor};

    frc::Spark left_LEDs{left_LED_controller_port};
    frc::Spark right_LEDs{right_LED_controller_port};
   
  public:
    MacroSuperstructure();
    void InitDefaultCommand() override;

    void SetAuto(bool auto_input);
    bool GetAuto();

    void SetFMSAuto(bool auto_input);
    bool GetFMSAuto();

    void SetInvertedAuto(bool input);
    int GetInvertedAuto();

    void SetVisionTargeting(bool targeting);
    int GetVisionTargeting();

    void SetProfile(int direction);
    int GetProfile();
    bool GetReset();

    void SetCompressor(bool state);
    double GetPressure();

    void SetLeftLEDs(double value);
    void SetRightLEDs(double value);
    void SetLEDs(double value);

    void SetEncoderFailure(bool fail);
    bool GetEncoderFailure();

    double CapValue(double value);
    double GetDirection(double x, double y);
};