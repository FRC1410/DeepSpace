#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class Drive : public frc::Command {
  private:
    double left_stick_amount, right_stick_amount;

    bool invert_driving = false;
    bool start_was_pressed = false;
    frc::Timer timer;
    //Rumble
    bool Rumble_State = false;

  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
