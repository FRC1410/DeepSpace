#pragma once

#include <frc/commands/Command.h>

class AutoElevatorCalibrate : public frc::Command {
  public:
    AutoElevatorCalibrate();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
