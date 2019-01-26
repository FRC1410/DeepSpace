#pragma once

#include <frc/commands/Command.h>

class Alerts : public frc::Command {
  public:
    Alerts();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
