/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class MacroControl : public frc::Command {
  private:
    bool l_was_pressed = false;
    bool r_was_pressed = false;

    bool switch_was_true = false;
    bool failed_before = false;

    double color = 0.01;
    
    frc::Timer m_timer;
    frc::Timer warning_timer;
    frc::Timer rumble_timer;

    double limit_switch_time, failure_time;

    bool compressor_triggered = false;
  
  public:
    MacroControl();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
