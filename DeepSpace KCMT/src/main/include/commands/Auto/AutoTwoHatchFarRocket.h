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
    double x_position, z_position;
    double previous_distance, previous_angle;

    double height;
    int stage, search;
    
    double gyro_PID_value, distance_PID_value, limelight_PID_value;
    
    frc::Timer m_timer;
    double previous_timer, path_timer, stage_distance;

  public:
    AutoTwoHatchFarRocket();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};