#pragma once

#include <frc/commands/Command.h>

class MacroControl : public frc::Command {
  private:
    bool compressing = true;
    bool button_was_pressed = false;
  public:
    MacroControl();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
