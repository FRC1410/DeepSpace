#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class AutoBetterLineSensor : public frc::Command {
  private:
    frc::Timer timer;
    int step;
    
  public:
    AutoBetterLineSensor();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};