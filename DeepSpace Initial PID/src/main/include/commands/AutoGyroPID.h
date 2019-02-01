#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoGyroPID : public frc::Command {
  private:
    double previous_angle, previous_timer, PID;

    frc::Timer timer;

  public:
    AutoGyroPID();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
