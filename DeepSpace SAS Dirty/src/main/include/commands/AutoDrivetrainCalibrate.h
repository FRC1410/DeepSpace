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
    int stage;
    double dists[10] = {};
    frc::Timer timer;
    int counter;
    double stage_distance, speed, calculated_friction;
    double acceleration_distance;
    double PID, previous_timer;
    double average_PID;
    double stage_angle;

  public:
    AutoDrivetrainCalibrate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
