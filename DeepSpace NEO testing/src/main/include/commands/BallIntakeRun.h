#pragma once

#include <frc/commands/Command.h>

class BallIntakeRun : public frc::Command {
  public:
    BallIntakeRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
