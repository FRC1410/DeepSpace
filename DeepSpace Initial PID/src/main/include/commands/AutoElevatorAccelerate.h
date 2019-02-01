#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoElevatorAccelerate : public frc::Command {
  private:
    double acceleration_time;
    double previous_height;
    double previous_timer;
    double max_speed;
    double deceleration_distance;
    double final_inputted_velocity;
    bool acceleration;

    double desired_height = 50;

    frc::Timer timer;

  public:
    AutoElevatorAccelerate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
