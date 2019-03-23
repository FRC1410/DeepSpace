/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ElevatorRun.h"
#include "Robot.h"

ElevatorRun::ElevatorRun() {
  Requires(&Robot::m_elevator);
}

// Called just before this Command runs the first time
void ElevatorRun::Initialize() {
  manual_control = true;

  low_button_was_pressed = false;
  mid_button_was_pressed = false;
  high_button_was_pressed = false;
  loading_station_button_was_pressed = false;
  reset_button_was_pressed = false;

  Robot::m_elevator.ResetIntegral();
  height = Robot::m_elevator.GetHeight();

  previous_profile = Robot::m_macro_superstructure.GetProfile();

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;

  left_fail_count = 0;
  right_fail_count = 0;

  Robot::m_macro_superstructure.SetEncoderFailure(false);
  Robot::m_elevator.ResetIntegral();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {
  if (encoder_failed = false) {
    if (Robot::m_elevator.GetLeftRevolutions() == 0) {
      left_fail_count++;
    } else {
      left_fail_count = 0;
    }

    if (Robot::m_elevator.GetRightRevolutions() == 0) {
      right_fail_count++;
    } else {
      right_fail_count = 0;
    }
    if ((left_fail_count >= encoder_fail_safety || right_fail_count >= encoder_fail_safety)) {
      Robot::m_macro_superstructure.SetEncoderFailure(true);
    }
  }

  if (Robot::m_macro_superstructure.GetAuto() == false) {
    elevator_input = -Robot::m_oi.GetOperatorAxis(elevator_axis);
    if (abs(elevator_input) > 0 && Robot::m_macro_superstructure.GetProfile() != 2) {
      manual_control = true;
      if (Robot::m_macro_superstructure.GetEncoderFailure() == false) {
        Robot::m_elevator.RunElevator(elevator_input + elevator_gravity);
      }
      Robot::m_macro_superstructure.SetHandoffStage(0);
    } else {
      if (Robot::m_oi.GetOperatorButton(elevator_loading_station_button) == true) {
        if (loading_station_button_was_pressed == false) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            if (height > elevator_min_height + elevator_loading_station_displacement) {
              height -= elevator_loading_station_displacement;
            } else {
              height = elevator_min_height;
            }
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_cargo_ship_height;
          }
        }
        loading_station_button_was_pressed = true;
      } else {
        loading_station_button_was_pressed = false;
      }

      if (Robot::m_oi.GetOperatorButton(elevator_high_position_button) == true) {
        if (high_button_was_pressed == false) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_high_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_high_ball_height;
          }
        }
        high_button_was_pressed = true;
      } else {
        high_button_was_pressed = false;
      }

      if (Robot::m_oi.GetOperatorButton(elevator_mid_position_button) == true) {
        if (mid_button_was_pressed == false) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_mid_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_mid_ball_height;
          }
        }
        mid_button_was_pressed = true;
      } else {
        mid_button_was_pressed = false;
      }

      if (Robot::m_oi.GetOperatorButton(elevator_low_position_button) == true) {
        if (low_button_was_pressed == false) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            height = elevator_low_hatch_height;
          } else if (Robot::m_macro_superstructure.GetProfile() == 1) {
            height = elevator_low_ball_height;
          }
        }
        low_button_was_pressed = true;
      } else {
        low_button_was_pressed = false;
      }

      if (Robot::m_macro_superstructure.GetHandoffStage() == 3) {
        if (previous_profile < 3) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
        }
        height = elevator_handoff_height;
        if (abs(height - Robot::m_elevator.GetHeight()) < elevator_deadband) {
          Robot::m_macro_superstructure.SetHandoffStage(4);
        }
      } else if (Robot::m_macro_superstructure.GetHandoffStage() == 5) {
        if (previous_profile < 5) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
        }
        height = elevator_handoff_height + elevator_handoff_raise;
        if (abs(height - Robot::m_elevator.GetHeight()) < elevator_deadband) {
          Robot::m_macro_superstructure.SetHandoffStage(0);
        }
      }

      if (Robot::m_macro_superstructure.GetReset() == true) {
        if (reset_button_was_pressed == false) {
          manual_control = false;
          Robot::m_elevator.ResetIntegral();
          height = elevator_min_height;
        }
        reset_button_was_pressed = true;
      } else {
        reset_button_was_pressed = false;
      }
      
      if (Robot::m_macro_superstructure.GetEncoderFailure() == false && manual_control == false) {
        Robot::m_elevator.Goto(height, m_timer.Get() - previous_timer);
      } else {
        Robot::m_elevator.RunElevator(elevator_gravity);
      }
    }
  }
  
  frc::SmartDashboard::PutNumber("Elevator Height", Robot::m_elevator.GetHeight());
  previous_timer = m_timer.Get();
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