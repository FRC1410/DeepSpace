#pragma once

#include <frc/commands/Command.h>

class Drive : public frc::Command {
  private:
    double left_stick_amount;
    double right_stick_amount;
  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
