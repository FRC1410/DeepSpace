#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoElevatorAccelerate : public frc::Command {
  private:
    double elevator_encoder;
    double acceleration_time;
    double previous_height;

    frc::Timer timer;

 public:
  AutoElevatorAccelerate();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
