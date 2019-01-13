#pragma once

#include <frc/commands/Command.h>

class HatchWheelsRun : public frc::Command {
  public:
    HatchWheelsRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};