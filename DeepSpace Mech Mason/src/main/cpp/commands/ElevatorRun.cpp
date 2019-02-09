#include "commands/ElevatorRun.h"
#include "Robot.h"

ElevatorRun::ElevatorRun() {
  Requires(&Robot::m_elevator);
}

// Called just before this Command runs the first time
void ElevatorRun::Initialize() {
  timer.Start();
  timer.Reset();
  previous_height = Robot::m_elevator.GetHeight();
  Robot::m_elevator.ResetIntegral();
  height = elevator_min_height;
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    elevator_input = -Robot::m_oi.GetOperatorAxis(elevator_axis, operator_deadzone);
    if (abs(elevator_input) > 0) {
      manual_control = true;
      if (acceleration_complete == false) {
        Robot::m_elevator.Accelerate(elevator_input, 0);
        if (elevator_input == Robot::m_elevator.GetInput()) {
          acceleration_complete = true;
        }
      } else {
        Robot::m_elevator.RunElevator(elevator_input, 0);
      }
    } else {
      if (manual_control == true) {
        height = Robot::m_elevator.GetHeight();
      }
      manual_control = false;
      acceleration_complete = false;
      if (Robot::m_oi.GetOperatorButton(elevator_loading_station_button) == true) {
        if (loading_station_button_was_pressed == false) {
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            if (height > elevator_min_height + elevator_loading_station_displacement) {
              height -= 3.5;
            } else {
              height = elevator_min_height;
            }
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_cargo_ship_height;
          }
        }
        loading_station_button_was_pressed == true;
      } else {
        loading_station_button_was_pressed == false;
      }
      if (Robot::m_oi.GetOperatorButton(elevator_high_position_button) == true) {
        if (high_button_was_pressed == false) {
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_high_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_high_ball_height;
          }
        }
        high_button_was_pressed == true;
      } else {
        high_button_was_pressed == false;
      }
      if (Robot::m_oi.GetOperatorButton(elevator_mid_position_button) == true) {
        if (mid_button_was_pressed == false) {
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_mid_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_mid_ball_height;
          }
        }
        mid_button_was_pressed == true;
      } else {
        mid_button_was_pressed == false;
      }
      if (Robot::m_oi.GetOperatorButton(elevator_low_position_button) == true) {
        if (low_button_was_pressed == false) {
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_low_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_low_ball_height;
          }
        }
        low_button_was_pressed == true;
      } else {
        low_button_was_pressed == false;
      }
      if (Robot::m_macro_superstructure.GetReset() == true) {
        if (reset_button_was_pressed == false) {
          height = elevator_min_height;
        }
        reset_button_was_pressed = true;
      } else {
        reset_button_was_pressed = false;
      }
      Robot::m_elevator.Goto(height, previous_height, timer.Get());
    }
  }
  previous_height = Robot::m_elevator.GetHeight();
  frc::SmartDashboard::PutNumber("Elevator Height", previous_height);
  frc::SmartDashboard::PutNumber("Target Height", height);

  frc::SmartDashboard::PutNumber("Left NEO Temperature", Robot::m_elevator.GetLeftTemperature());
  frc::SmartDashboard::PutNumber("Right NEO Temperature", Robot::m_elevator.GetRightTemperature());
  timer.Reset();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void ElevatorRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRun::Interrupted() {}