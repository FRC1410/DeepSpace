#pragma once

#include <frc/commands/Command.h>

class MacroControl : public frc::Command {
 public:
  MacroControl();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
