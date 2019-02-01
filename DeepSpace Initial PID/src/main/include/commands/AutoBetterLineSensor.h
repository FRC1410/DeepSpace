#pragma once

#include <frc/commands/Command.h>

class AutoBetterLineSensor : public frc::Command {
 public:
  AutoBetterLineSensor();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
