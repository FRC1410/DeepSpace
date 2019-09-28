/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive.h"
#include "Robot.h"

Drive::Drive() {
  Requires(&Robot::m_drivetrain);
}

// Called just before this Command runs the first time
void Drive::Initialize() {
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;

  Robot::m_limelight.SetTargetFound(false);

  turn_left_was_pressed = false;
  turn_right_was_pressed = false;

  invert_driving = true;
  invert_button_was_pressed = false;
  invert_timer = 0;

  dpad_left_was_pressed = false;
  dpad_right_was_pressed = false;
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  Robot::m_drivetrain.IncrementX((Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));
  Robot::m_drivetrain.IncrementZ((Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));

  Robot::m_limelight.SetPIDConstants();
  Robot::m_drivetrain.SetPIDConstants();

  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
      if (invert_button_was_pressed == false) {
        invert_timer = m_timer.Get();
        invert_driving = !invert_driving;
      }
      invert_button_was_pressed = true;
    } else {
      invert_button_was_pressed = false;
    }

    //if (Robot::m_oi.GetDriverAxis(vision_align_axis) >= trigger_threshold) {
    if (Robot::m_oi.GetDriverButton(vision_align_button) == true) {
      //if (Robot::m_limelight.GetTargetFound() == false) {
        Robot::m_limelight.SetPipeline(limelight_vision_pipeline);
      //}

      if (vision_button_was_pressed == false) {
        Robot::m_limelight.ResetAngleIntegral();
        Robot::m_limelight.ResetAreaIntegral();
      }

      vision_button_was_pressed = true;

      if (Robot::m_limelight.GetTarget() == false) {
        Robot::m_oi.SetDriverRumble(0.5, 0.5);

        //if (Robot::m_oi.GetDriverAxis(invert_driving_axis) >= trigger_threshold) {
        if (invert_driving == true) {
          Robot::m_drivetrain.SetCurvedSpeed(Robot::m_oi.GetAverageDriverInput(), Robot::m_oi.GetAverageDriverInput());
        } else {
          Robot::m_drivetrain.SetCurvedSpeed(-Robot::m_oi.GetAverageDriverInput(), -Robot::m_oi.GetAverageDriverInput());
        }
      } else {
        Robot::m_oi.SetDriverRumble(0, 0);

        if (Robot::m_limelight.GetTargetArea() < limelight_large_area) {
          PID_value = Robot::m_limelight.GetAnglePID(limelight_target_offset_offset + Robot::m_limelight.GetAreaPID(limelight_large_area, m_timer.Get() - previous_timer), m_timer.Get() - previous_timer);
        } else {
        //  Robot::m_limelight.SetTargetFound(true);
          PID_value = 0;
        }

        /*if (Robot::m_limelight.GetTargetFound() == true) {
          Robot::m_limelight.SetPipeline(limelight_driver_pipeline);
        }*/

        //if (Robot::m_oi.GetDriverAxis(invert_driving_axis) > trigger_threshold) {
        if (invert_driving == true) {
          Robot::m_drivetrain.SetCurvedSpeed(Robot::m_oi.GetAverageDriverInput() - PID_value, Robot::m_oi.GetAverageDriverInput() + PID_value);
        } else {
          Robot::m_drivetrain.SetCurvedSpeed(-Robot::m_oi.GetAverageDriverInput() - PID_value, -Robot::m_oi.GetAverageDriverInput() + PID_value);
        }
      }
    } else {
      Robot::m_limelight.SetPipeline(limelight_driver_pipeline);
      vision_button_was_pressed = false;
      Robot::m_limelight.SetTargetFound(false);
      Robot::m_oi.SetDriverRumble(0, 0);

      /*if (Robot::m_oi.GetDriverButton(drivetrain_turn_left_button) == true) {
        if (turn_left_was_pressed == false) {
          Robot::m_drivetrain.ResetGyroIntegral();
          reference_angle = Robot::m_drivetrain.GetAngle();
        }
        goto turn_left;
        turn_left_was_pressed = true;
      } else {
        turn_left_was_pressed = false;
      }

      if (Robot::m_oi.GetDriverButton(drivetrain_turn_right_button) == true) {
        if (turn_right_was_pressed == false) {
          Robot::m_drivetrain.ResetGyroIntegral();
          reference_angle = Robot::m_drivetrain.GetAngle();
        }
        goto turn_right;
      } else {
        turn_right_was_pressed = false;
      }*/

      //if (Robot::m_oi.GetDriverAxis(invert_driving_axis) >= trigger_threshold) {
      if (invert_driving == true) {
        if (Robot::m_oi.GetDriverButton(drivetrain_straight_drive_button) == true) {
          Robot::m_drivetrain.SetCurvedSpeed(Robot::m_oi.GetAverageDriverInput(), Robot::m_oi.GetAverageDriverInput());
        } else {
          Robot::m_drivetrain.SetCurvedSpeed(Robot::m_oi.GetDriverAxis(drivetrain_right_axis), Robot::m_oi.GetDriverAxis(drivetrain_left_axis));
        }
      } else {
        if (Robot::m_oi.GetDriverButton(drivetrain_straight_drive_button) == true) {
          Robot::m_drivetrain.SetCurvedSpeed(-Robot::m_oi.GetAverageDriverInput(), -Robot::m_oi.GetAverageDriverInput());
        } else {
          Robot::m_drivetrain.SetCurvedSpeed(-Robot::m_oi.GetDriverAxis(drivetrain_left_axis), -Robot::m_oi.GetDriverAxis(drivetrain_right_axis));
        }
      }

      if (false) {
        turn_left:
          PID_value = Robot::m_drivetrain.GetGyroPID(reference_angle - 90, m_timer.Get() - previous_timer);
          Robot::m_drivetrain.SetCurvedSpeed(PID_value, -PID_value);
      } else if (false) {
        turn_right:
          PID_value = Robot::m_drivetrain.GetGyroPID(reference_angle + 90, m_timer.Get() - previous_timer);
          Robot::m_drivetrain.SetCurvedSpeed(PID_value, -PID_value);
      }

      if ((invert_driving == true && ((m_timer.Get() - invert_timer) < double_rumble_time || ((m_timer.Get() - invert_timer) > (2 * double_rumble_time) && (m_timer.Get() - invert_timer) < (3 * double_rumble_time)))) || (invert_driving == false && (m_timer.Get() - invert_timer) < single_rumble_time)) {
        Robot::m_oi.SetDriverRumble(1, 1);
      }
    }
  }

  Robot::m_drivetrain.DisplayData((Robot::m_drivetrain.GetDistance() - previous_distance) / (m_timer.Get() - previous_timer), ((Robot::m_drivetrain.GetAngle() - previous_angle) / (m_timer.Get() - previous_timer)) * pi / 180, Robot::m_oi.GetDriverAxis(invert_driving_axis) >= trigger_threshold);
  Robot::m_limelight.GetTarget();
  Robot::m_limelight.GetTargetX();
  Robot::m_limelight.GetTargetArea();

  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_timer = m_timer.Get();

  /*if (Robot::m_oi.GetOperatorAxis(limelight_offset_increase_trigger) >= trigger_threshold){
    limelight_target_offset_offset += 0.0254;  
  } else if (Robot::m_oi.GetOperatorAxis(limelight_offset_decrease_trigger) >= trigger_threshold) {
    limelight_target_offset_offset -= 0.0254;
  }

  if (Robot::m_oi.GetDriverDPad() == 90) {
    if (dpad_left_was_pressed == false) {
      limelight_target_offset_offset += 0.148;
    }
    dpad_left_was_pressed = true;
  } else {
    dpad_left_was_pressed = false;
  }

  if (Robot::m_oi.GetDriverDPad() == 270) {
    if (dpad_right_was_pressed == false) {
      limelight_target_offset_offset -= 0.148;
    }
    dpad_right_was_pressed = true;
  } else {
    dpad_right_was_pressed = false;
  }*/
  
  frc::SmartDashboard::PutNumber("target offset offset" , limelight_target_offset_offset);
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}