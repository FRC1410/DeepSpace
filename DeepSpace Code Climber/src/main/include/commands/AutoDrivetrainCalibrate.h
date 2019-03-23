/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoDrivetrainCalibrate : public frc::Command {
  private:
    int stage, counter;
    double dists[10];
    double stage_distance, stage_angle, acceleration_distance;
    double speed, calculated_friction;
    double PID, average_PID;

    frc::Timer m_timer;
    double previous_timer;

  public:
    AutoDrivetrainCalibrate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
