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
    bool invert_driving, invert_button_was_pressed;
    
    double previous_distance, previous_angle;
    double previous_x[25], previous_z[25], previous_angles[25], previous_times[25];
    int search;

    double PID_value, limelight_PID_value;
    double limelight_x, limelight_angle;
    double latency_x, latency_z, latency_angle;
    bool target_found, vision_button_was_pressed, limelight_toggle_was_pressed;

    double invert_timer, previous_timer, vision_timer;
    frc::Timer m_timer;

  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
