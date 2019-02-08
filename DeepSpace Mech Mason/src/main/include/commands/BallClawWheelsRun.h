#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class BallClawWheelsRun : public frc::Command {
  private:
    bool switch_was_true = false;
    frc::Timer rumble_timer;
  public:
    BallClawWheelsRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
