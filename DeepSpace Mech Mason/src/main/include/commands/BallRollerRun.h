#pragma once

#include <frc/commands/Command.h>

class BallRollerRun : public frc::Command {
  private:
    bool button_was_pressed = false;
    bool roller_extended = true;
    
  public:
    BallRollerRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
