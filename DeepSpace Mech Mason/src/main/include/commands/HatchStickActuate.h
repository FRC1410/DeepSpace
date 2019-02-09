#pragma once

#include <frc/commands/Command.h>

class HatchStickActuate : public frc::Command {
  private:
    bool button_was_pressed = false;
    
  public:
    HatchStickActuate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
