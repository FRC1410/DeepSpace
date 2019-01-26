#pragma once

#include <frc/commands/Command.h>

class BallRollerRun : public frc::Command {
  public:
    BallRollerRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
