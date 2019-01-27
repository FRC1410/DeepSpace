#pragma once

#include <frc/commands/Command.h>

class HatchPickupRotate : public frc::Command {
  private:
    double hatch_rotator_input;
    
  public:
    HatchPickupRotate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
