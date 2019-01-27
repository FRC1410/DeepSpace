#pragma once

#include <frc/commands/Command.h>

class ClimberExtend : public frc::Command {
  private:
    bool front_button_was_pressed = false;
    bool back_button_was_pressed = false;
    bool front_extended = false;
    bool back_extended = false;
    
  public:
    ClimberExtend();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
