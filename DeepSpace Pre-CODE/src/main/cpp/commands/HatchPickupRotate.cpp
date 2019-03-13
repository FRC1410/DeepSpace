/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchPickupRotate.h"
#include "Robot.h"

HatchPickupRotate::HatchPickupRotate() {
  Requires(&Robot::m_hatch_pickup);
}

// Called just before this Command runs the first time
void HatchPickupRotate::Initialize() {
  button_was_pressed = Robot::m_oi.GetOperatorButton(hatch_pickup_rotator_button);
  manual_control = false;

  handoff_timer.Reset();
  handoff_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void HatchPickupRotate::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    hatch_rotator_input = -Robot::m_oi.GetOperatorAxis(hatch_pickup_rotator_axis);

    if (abs(hatch_rotator_input) > 0) {
      manual_control = true;
      Robot::m_hatch_pickup.RotatePickup(hatch_rotator_input);
      Robot::m_macro_superstructure.SetHandoffStage(0);
    } else {
      if (manual_control == true) {
        if (Robot::m_hatch_pickup.GetPosition() < (hatch_pickup_down_position + hatch_pickup_up_position) / 2) {
          Robot::m_hatch_pickup.SetState(true);
        } else {
          Robot::m_hatch_pickup.SetState(false);
        }
      }
      manual_control = false;

      if (Robot::m_oi.GetOperatorButton(hatch_pickup_toggle_button) == true) {
        if (button_was_pressed == false) {
          if (Robot::m_macro_superstructure.GetProfile() == 0) {
            if (Robot::m_hatch_pickup.GetState() == true) {
              Robot::m_hatch_pickup.SetState(false);
            } else {
              Robot::m_hatch_pickup.SetState(true);
              Robot::m_macro_superstructure.SetHandoffStage(1);
            }
          }
        }
        button_was_pressed = true;
      } else {
        button_was_pressed = false;
      }

      if (Robot::m_macro_superstructure.GetReset() == true) {
        Robot::m_hatch_pickup.SetState(true);
      }

      if (Robot::m_hatch_pickup.GetState() == true) {
        if (Robot::m_macro_superstructure.GetHandoffStage() == 0) {
          if (Robot::m_hatch_pickup.GetPosition() > hatch_pickup_up_position) {
            Robot::m_hatch_pickup.RotatePickup(hatch_pickup_up_power);
          } else {
            Robot::m_hatch_pickup.RotatePickup(0);
          }
        } else if (Robot::m_macro_superstructure.GetHandoffStage() == 1) {
          if (Robot::m_hatch_pickup.GetPosition() < hatch_pickup_down_position) {
            Robot::m_hatch_pickup.RotatePickup(hatch_pickup_down_power);
          } else if (Robot::m_hatch_pickup.GetPosition() >= hatch_pickup_down_position){
            Robot::m_hatch_pickup.RotatePickup(0);
            Robot::m_macro_superstructure.SetHandoffStage(2);
          }
        } else if (Robot::m_macro_superstructure.GetHandoffStage() == 4) {
          Robot::m_hatch_pickup.RotatePickup(hatch_pickup_up_power);
          if (Robot::m_hatch_pickup.GetPosition() > hatch_pickup_up_position) {
            handoff_timer.Reset();
          } else {
            if (handoff_timer.Get() > hatch_handoff_time) {
              Robot::m_macro_superstructure.SetHandoffStage(5);
            }
          }
        }
      } else {
        if (Robot::m_hatch_pickup.GetPosition() < hatch_pickup_down_position) {
          Robot::m_hatch_pickup.RotatePickup(hatch_pickup_down_power);
        } else {
          Robot::m_hatch_pickup.RotatePickup(hatch_pickup_stall_power);
        }
      }
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchPickupRotate::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void HatchPickupRotate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchPickupRotate::Interrupted() {}