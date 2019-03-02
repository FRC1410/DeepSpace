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
    bool invert_driving = false;
    bool invert_button_was_pressed = false;
    double x_position, y_position, previous_distance, previous_angle, previous_y, PID_value, limelight_PID_value;
    bool vision_align_was_pressed, vision_aligning;
    
    frc::Timer rumble_timer;
    frc::Timer timer;
    frc::Timer vision_timer;
    frc::Timer rumble_timer2;

  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
