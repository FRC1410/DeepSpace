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
  invert_driving = true;
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();

  m_timer.Reset();
  m_timer.Start();

  invert_timer = 0;
  previous_timer = -0.02;

  invert_button_was_pressed = Robot::m_oi.GetDriverButton(invert_driving_button);
  vision_button_was_pressed = Robot::m_oi.GetDriverButton(vision_align_button);
  limelight_toggle_was_pressed = Robot::m_oi.GetDriverButton(limelight_toggle_button);
  
  if (Robot::m_macro_superstructure.GetAuto() == false && Robot::m_macro_superstructure.GetFMSAuto() == true) {
    Robot::m_limelight.SetPipeline(0);
    Robot::m_limelight.TurnOffLights();
  }
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  Robot::m_drivetrain.IncrementX((Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));
  Robot::m_drivetrain.IncrementZ((Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));

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

    if (Robot::m_oi.GetDriverButton(vision_align_button) == true) {
      Robot::m_limelight.SetPipeline(1);
      Robot::m_limelight.TurnOnLights();

      if (vision_button_was_pressed == false) {
        Robot::m_limelight.ResetIntegral();
      }

      vision_button_was_pressed = true;
      Robot::m_macro_superstructure.SetVisionTargeting(true);

      if (Robot::m_limelight.GetTarget() == false) {
        Robot::m_oi.SetDriverRumbleLeft(0.5);
        Robot::m_oi.SetDriverRumbleRight(0.5);
        goto manual_control;
      } else {
        PID_value = Robot::m_limelight.GetPID(limelight_target_offset, m_timer.Get() - previous_timer);
        if (invert_driving == true) {
          Robot::m_drivetrain.CurvedAccelerate(Robot::m_drivetrain.GetCurvedSpeed(Robot::m_oi.GetAverageDriverInput()) + PID_value, Robot::m_drivetrain.GetCurvedSpeed(Robot::m_oi.GetAverageDriverInput()) - PID_value, m_timer.Get() - previous_timer);
        } else {
          Robot::m_drivetrain.CurvedAccelerate(-Robot::m_drivetrain.GetCurvedSpeed(Robot::m_oi.GetAverageDriverInput()) + PID_value, -Robot::m_drivetrain.GetCurvedSpeed(Robot::m_oi.GetAverageDriverInput()) - PID_value, m_timer.Get() - previous_timer);
        }
      }
    } else {
      Robot::m_limelight.SetPipeline(0);
      Robot::m_limelight.TurnOffLights();
      
      vision_button_was_pressed = false;
      Robot::m_macro_superstructure.SetVisionTargeting(false);
      
      Robot::m_oi.SetDriverRumbleLeft(0);
      Robot::m_oi.SetDriverRumbleRight(0);

      manual_control:
        left_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_left_axis);
        right_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_right_axis);

        if (invert_driving == false) {
          if ((m_timer.Get() - invert_timer) < single_rumble_time && Robot::m_macro_superstructure.GetVisionTargeting() == false) {
            Robot::m_oi.SetDriverRumbleLeft(1);
            Robot::m_oi.SetDriverRumbleRight(1);
          } else {
            Robot::m_oi.SetDriverRumbleLeft(0);
            Robot::m_oi.SetDriverRumbleRight(0);
          }
        } else {
          if ((m_timer.Get() - invert_timer) < double_rumble_time || ((m_timer.Get() - invert_timer) > (2 * double_rumble_time) && (m_timer.Get() - invert_timer) < (3 * double_rumble_time)) && Robot::m_macro_superstructure.GetVisionTargeting() == false) {
            Robot::m_oi.SetDriverRumbleLeft(1);
            Robot::m_oi.SetDriverRumbleRight(1);
          } else {
            Robot::m_oi.SetDriverRumbleLeft(0);
            Robot::m_oi.SetDriverRumbleRight(0);
          }
        }

        if (invert_driving == false) {
          Robot::m_drivetrain.SetSpeed(left_stick_amount, right_stick_amount); 
        } else {
          Robot::m_drivetrain.SetSpeed(-right_stick_amount, -left_stick_amount);
        }
    }
  }

  frc::SmartDashboard::PutNumber("X", Robot::m_drivetrain.GetX());
  frc::SmartDashboard::PutNumber("Z", Robot::m_drivetrain.GetZ());

  frc::SmartDashboard::PutNumber("Tx", Robot::m_limelight.GetTargetX());
  frc::SmartDashboard::PutNumber("Ta", Robot::m_limelight.GetTargetArea());

  frc::SmartDashboard::PutNumber("PID", PID_value);

  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_timer = m_timer.Get();
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