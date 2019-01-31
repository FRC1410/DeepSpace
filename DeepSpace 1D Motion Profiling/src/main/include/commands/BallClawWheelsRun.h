#pragma once

#include <frc/commands/Command.h>

class BallClawWheelsRun : public frc::Command {
  public:
    BallClawWheelsRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
