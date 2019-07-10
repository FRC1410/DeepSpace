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

class MacroControl : public frc::Command {
  private:    
    bool compressor_triggered;
    bool switch_was_true = false;
    
    double defense_color = (round((defense_led_max + defense_led_min) * 25) / 50) - 0.01;
    bool down_cycle_pressed = false;
    bool up_cycle_pressed = false;

    double penalty_color = lime_preset;
    bool penalty_increment_pressed = false;

    double color = 0.01;
    bool cycle_negative_was_pressed, cycle_positive_was_pressed;
    
    frc::Timer m_timer;
    frc::Timer rumble_timer;
    frc::Timer warning_timer;
    frc::Timer penalty_cooldown_timer;
  
  public:
    MacroControl();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};