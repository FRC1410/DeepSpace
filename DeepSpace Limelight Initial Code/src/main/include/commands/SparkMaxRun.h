#pragma once

#include <frc/commands/Command.h>

class SparkMaxRun : public frc::Command {
  private:
    double stick_input;
  public:
    SparkMaxRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
