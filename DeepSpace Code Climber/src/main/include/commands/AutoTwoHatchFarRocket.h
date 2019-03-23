/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoTwoHatchFarRocket : public frc::Command {
  private:
    double x_position, z_position, height;
    double previous_distance, previous_angle;
    int stage, search;
    
    frc::Timer m_timer;
    double previous_timer, path_timer, stage_distance;

    double previous_x[25], previous_z[25], previous_angles[25], previous_times[25];
    bool target_found;
    double limelight_x, limelight_z, limelight_angle;
    double latency_x, latency_z, latency_angle;
    double gyro_PID_value, distance_PID_value, limelight_PID_value;

  public:
    AutoTwoHatchFarRocket();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
