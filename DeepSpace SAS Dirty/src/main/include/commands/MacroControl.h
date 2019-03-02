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
    bool compressing = true;
    bool button_was_pressed = false;
    bool l_was_pressed = false;
    bool r_was_pressed = false;

    bool switch_was_true = false;
    double white = 0.93;
    double color = 0.01;
    
    frc::Timer flex_timer;
  
  public:
    MacroControl();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
