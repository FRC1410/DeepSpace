#pragma once

#include <frc/commands/Command.h>

class HatchStickActuate : public frc::Command {
  private:
    bool select_was_pressed = false;
    bool stick_extended = false;
  public:
    HatchStickActuate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
