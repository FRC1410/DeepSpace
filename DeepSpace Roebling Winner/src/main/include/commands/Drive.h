/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class Drive : public frc::Command {
  private:
    double left_stick_amount, right_stick_amount;
    
    bool invert_button_was_pressed, invert_driving;
    double invert_timer;
    
    double PID_value;
    bool vision_button_was_pressed, target_found;

    bool turn_right_was_pressed, turn_left_was_pressed;
    double reference_angle;

    double previous_distance, previous_angle, previous_timer;
    frc::Timer m_timer;

  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};