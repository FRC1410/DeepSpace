/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoElevatorCalibrate : public frc::Command {
  private:
    double revs [10] = {};
    int counter, stage;
    double speed, calculated_strong_gravity, calculated_weak_gravity;
    double stage_height, height_error, acceleration_distance;
    double previous_timer;

    frc::Timer timer;

  public:
    AutoElevatorCalibrate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};

