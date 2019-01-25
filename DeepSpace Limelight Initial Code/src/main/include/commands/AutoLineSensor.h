#pragma once

#include <frc/commands/Command.h>

class AutoLineSensor : public frc::Command {
  public:
    AutoLineSensor();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
