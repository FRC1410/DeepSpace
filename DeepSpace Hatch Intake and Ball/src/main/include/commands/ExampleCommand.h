#pragma once

#include <frc/commands/Command.h>

class ExampleCommand : public frc::Command {
  public:
    ExampleCommand();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
