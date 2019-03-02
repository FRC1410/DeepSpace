/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

#include "RobotMap.h"

class ElevatorRun : public frc::Command {
  private:
    double elevator_input;
    bool manual_control, acceleration_complete;
    bool low_button_was_pressed, mid_button_was_pressed, high_button_was_pressed, loading_station_button_was_pressed, reset_button_was_pressed;
    int previous_profile;
    double height, previous_height;
    frc::Timer timer;
    
  public:
    ElevatorRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};