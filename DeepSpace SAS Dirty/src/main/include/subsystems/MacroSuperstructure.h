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
#include <AHRS.h>

#include "RobotMap.h"

class MacroSuperstructure : public frc::Subsystem {
  private:
    int profile = 0;
    bool reset = false;

    frc::Spark left_LEDs{left_LED_controller_port};
    frc::Spark right_LEDs{right_LED_controller_port};

    bool running_auto;
    int handoff_state;
   
    frc::Compressor compressor;

    AnalogInput pressure_input{pressure_sensor};

  public:
    MacroSuperstructure();
    void InitDefaultCommand() override;
    double CapValue(double value);
    void SetProfile(int direction);
    int GetProfile();
    bool GetReset();
    void SetLeftLEDs(double value);
    void SetRightLEDs(double value);
    void SetLEDs(double value);
    void SetAuto(bool auto_input);
    bool GetAuto();
    void StartCompressor();
    void StopCompressor();    
    double GetPressure();
    int GetHandoffState();
    int SetHandoffState(int state);
};