#pragma once

#include <frc/commands/Command.h>

class AutoLimelightTargeting : public frc::Command {
  public:
    AutoLimelightTargeting();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
