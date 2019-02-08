#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

class Drive : public frc::Command {
  private:
    double left_stick_amount, right_stick_amount;
    bool invert_driving = false;
    bool invert_button_was_pressed = false;
    double x_position, y_position;
    double previous_timer, previous_left_speed, previous_right_speed, previous_distance;
    
    frc::Timer rumble_timer;
    frc::Timer timer;

  public:
    Drive();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
