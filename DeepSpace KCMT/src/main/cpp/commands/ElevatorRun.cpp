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
  manual_control = false;

  low_button_was_pressed = false;
  mid_button_was_pressed = false;
  high_button_was_pressed = false;
  loading_station_button_was_pressed = false;
  reset_button_was_pressed = false;

  height = Robot::m_elevator.GetHeight();

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (elevator_defense_manual_control == true || Robot::m_macro_superstructure.GetProfile() != defense_profile_number) {
      elevator_input = -pow(Robot::m_oi.GetOperatorAxis(elevator_axis), 3);
      if (abs(elevator_input) > 0) {
        manual_control = true;
        Robot::m_elevator.RunElevator(elevator_input + elevator_gravity);
      } else {
        if (Robot::m_macro_superstructure.GetProfile() != defense_profile_number) {
          if (Robot::m_oi.GetOperatorButton(elevator_loading_station_button) == true) {
            if (loading_station_button_was_pressed == false) {
              manual_control = false;
              Robot::m_elevator.ResetIntegral();
              if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
                if (height > elevator_min_height + elevator_loading_station_displacement) {
                  height -= elevator_loading_station_displacement;
                } else {
                  height = elevator_min_height;
                }
              } else {
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
              if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
                height = elevator_high_hatch_height;
              } else {
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
              if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
                height = elevator_mid_hatch_height;
              } else {
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
              if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
                height = elevator_low_hatch_height;
              } else {
                height = elevator_low_ball_height;
              }
            }
            low_button_was_pressed = true;
          } else {
            low_button_was_pressed = false;
          }

          if (Robot::m_macro_superstructure.GetReset() == true) {
            if (reset_button_was_pressed == false) {
              manual_control = false;
              Robot::m_elevator.ResetIntegral();
            }
            height = elevator_min_height;
            reset_button_was_pressed = true;
          } else {
            reset_button_was_pressed = false;
          }
        }
        if (manual_control == false) {
          Robot::m_elevator.Goto(height, m_timer.Get() - previous_timer);
        } else {
          Robot::m_elevator.RunElevator(elevator_gravity);
        }
      }
    } else {
      Robot::m_elevator.RunElevator(0);
    }
  }
  
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