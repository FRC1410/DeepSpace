#pragma once

#include <frc/commands/Command.h>

class AutoDistancePID : public frc::Command {
 public:
  AutoDistancePID();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
