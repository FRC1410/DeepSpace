#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoBetterLineSensor : public frc::Command {
 public:
  AutoBetterLineSensor();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

 private:
  frc::Timer timer;
};
