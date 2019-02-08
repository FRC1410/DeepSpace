#pragma once

#include <frc/commands/Command.h>
#include <frc/Timer.h>

#include "RobotMap.h"

class ElevatorRun : public frc::Command {
  private:
    double elevator_input;
    bool manual_control = false;
    bool acceleration_complete = false;
    bool low_button_was_pressed = false;
    bool mid_button_was_pressed = false;
    bool high_button_was_pressed = false;
    bool loading_station_button_was_pressed = false;
    bool reset_button_was_pressed = false;

    double height = elevator_min_height;
    double previous_height;

    frc::Timer timer;
    
  public:
    ElevatorRun();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};