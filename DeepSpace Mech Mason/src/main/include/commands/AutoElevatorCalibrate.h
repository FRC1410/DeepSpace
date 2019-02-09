#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoElevatorCalibrate : public frc::Command {
  private:
    double revs [10] = {};
    int counter, stage;
    double speed, calculated_strong_gravity, calculated_weak_gravity;
    double previous_timer, stage_height, height_error, acceleration_distance;

    frc::Timer timer;

  public:
    AutoElevatorCalibrate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};