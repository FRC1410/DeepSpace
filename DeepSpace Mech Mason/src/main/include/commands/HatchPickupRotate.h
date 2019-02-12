#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class HatchPickupRotate : public frc::Command {
  private:
    double hatch_rotator_input;
    bool button_was_pressed, manual_control;

    frc::Timer timer;

  public:
    HatchPickupRotate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
