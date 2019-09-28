/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class ElevatorRun : public frc::Command {
  private:
    double elevator_input, height;
    bool manual_control;
    
    bool low_button_was_pressed, mid_button_was_pressed, high_button_was_pressed;
    bool loading_station_button_was_pressed, reset_button_was_pressed;

    frc::Timer m_timer;
    double previous_timer;
    
  public:
    ElevatorRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};