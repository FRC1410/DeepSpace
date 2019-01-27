#pragma once

#include <frc/commands/Command.h>

class ElevatorRun : public frc::Command {
  private:
    double elevator_input;
    
  public:
    ElevatorRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
