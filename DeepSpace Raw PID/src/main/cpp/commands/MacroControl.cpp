/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MacroControl.h"
#include "Robot.h"

MacroControl::MacroControl() {
  Requires(&Robot::m_macro_superstructure);
}

// Called just before this Command runs the first time
void MacroControl::Initialize() {
  m_timer.Reset();
  m_timer.Start();

  rumble_timer.Reset();
  rumble_timer.Start();

  limit_switch_time = 0;
  failure_time = -1;

  failed_before = false;
  switch_was_true = false;

  warning_timer.Reset();
  warning_timer.Stop();

  frc::SmartDashboard::PutBoolean("Warnings", false);
  frc::SmartDashboard::PutBoolean("Hatch", false);
  frc::SmartDashboard::PutBoolean("Cargo", false);
  frc::SmartDashboard::PutBoolean("Climber", false);

  compressor_triggered = false;
}

// Called repeatedly when this Command is scheduled to run
void MacroControl::Execute() {
  Robot::m_macro_superstructure.SetProfile(Robot::m_oi.GetOperatorDPad());
  if (Robot::m_macro_superstructure.GetReset() == false) {
    if (Robot::m_macro_superstructure.GetVisionTargeting() == false) {
      switch (Robot::m_macro_superstructure.GetProfile()) {
        case hatch_profile_number:
          frc::SmartDashboard::PutBoolean("Hatch", true);
          frc::SmartDashboard::PutBoolean("Cargo", false);
          frc::SmartDashboard::PutBoolean("Climber", false);
          Robot::m_macro_superstructure.SetLEDs(hatch_color);
          break;
        case ball_profile_number:
          frc::SmartDashboard::PutBoolean("Hatch", false);
          frc::SmartDashboard::PutBoolean("Cargo", true);
          frc::SmartDashboard::PutBoolean("Climber", false);
          if (Robot::m_ball_claw.GetLimitSwitch() == true) {
            if (switch_was_true == false) {
              rumble_timer.Reset();
              limit_switch_time = m_timer.Get();
            }
            switch_was_true = true;
          } else {
            switch_was_true = false;
          }

          if (m_timer.Get() - limit_switch_time < (blinking_LED_time * 5) && fmod(m_timer.Get() - limit_switch_time, blinking_LED_time * 2) < blinking_LED_time) {
            Robot::m_macro_superstructure.SetLEDs(ball_acquired_color);
          } else {
            Robot::m_macro_superstructure.SetLEDs(ball_color);
          }
          break;
        case climber_profile_number:
          frc::SmartDashboard::PutBoolean("Hatch", false);
          frc::SmartDashboard::PutBoolean("Cargo", false);
          frc::SmartDashboard::PutBoolean("Climber", true);
          Robot::m_macro_superstructure.SetLEDs(climber_color);
          break;
        }
    } else {
      Robot::m_macro_superstructure.SetLEDs(vision_targeting_color);
    }
  } else {
    Robot::m_macro_superstructure.SetLEDs(reset_mechanisms_color);
  }

  if (Robot::m_oi.GetHumanPlayerButton(LED_cycle_negative_button) == true) {
    if (l_was_pressed == false) {
      if (color > -0.98) {
        color -= 0.02;
      }
    }
  	l_was_pressed = true;
  } else {  
    l_was_pressed = false;
  }

  if (Robot::m_oi.GetHumanPlayerButton(LED_cycle_positive_button) == true) {
    if (r_was_pressed == false) {
      if (color < 0.98) {
        color += 0.02;
      }
    }
  	r_was_pressed = true;
  } else {  
    r_was_pressed = false;
  }

  if (Robot::m_macro_superstructure.GetEncoderFailure() == true) {
    if (failed_before == false) {
      failure_time = m_timer.Get();
    }
    failed_before = true;
  } else {
    failed_before = false;
  }

  if (m_timer.Get() - failure_time < (blinking_LED_time * 5) && fmod(m_timer.Get() - failure_time, blinking_LED_time * 2) < blinking_LED_time) {
    Robot::m_macro_superstructure.SetLEDs(encoder_fail_color);
  }

  if (Robot::m_oi.GetHumanPlayerAxis(0) != 0 || Robot::m_oi.GetHumanPlayerAxis(1) != 0 || Robot::m_oi.GetHumanPlayerAxis(4) != 0 || Robot::m_oi.GetHumanPlayerAxis(5) != 0) {
    Robot::m_macro_superstructure.SetLeftLEDs(color);
    Robot::m_macro_superstructure.SetRightLEDs(color);
    frc::SmartDashboard::PutNumber("Color", floor(color * 100) / 100);
  }

  frc::SmartDashboard::PutNumber("Match Time", frc::Timer::GetMatchTime());

  if (compressor_triggered == true) {
    Robot::m_macro_superstructure.SetCompressor(true);

    frc::Shuffleboard::GetTab("Debugging")
    .Add("Ball Roller", "Running");
    if (Robot::m_macro_superstructure.GetPressure() > compressor_high_thresh) {
      compressor_triggered = false;
    }
  } else {
    Robot::m_macro_superstructure.SetCompressor(false);
    
    frc::Shuffleboard::GetTab("Debugging")
    .Add("Compressor", "Idle");
  }

  if ((Robot::m_macro_superstructure.GetPressure() < compressor_low_thresh) || (Robot::m_oi.GetOperatorButton(toggle_compressor_button) == true) || (Robot::m_macro_superstructure.GetFMSAuto() == true)) {
    compressor_triggered = true;
  }

  if (Robot::m_macro_superstructure.GetFMSAuto() == true) {
    Robot::m_macro_superstructure.SetCompressor(true);
  }
  
  frc::SmartDashboard::PutNumber("Operator Profile", Robot::m_macro_superstructure.GetProfile());
  frc::SmartDashboard::PutNumber("Pressure", Robot::m_macro_superstructure.GetPressure());
  
  if (rumble_timer.Get() < double_rumble_time || (rumble_timer.Get() > (double_rumble_time * 2) && rumble_timer.Get() < (double_rumble_time * 3))) {
    Robot::m_oi.SetOperatorRumbleLeft(1);
    Robot::m_oi.SetOperatorRumbleRight(1);
  } else {
    Robot::m_oi.SetOperatorRumbleLeft(0);
    Robot::m_oi.SetOperatorRumbleRight(0);
  }

  if (frc::Timer::GetMatchTime() < rumble_time_alert && frc::Timer::GetMatchTime() > 1 && Robot::m_macro_superstructure.GetFMSAuto() == false) {
    warning_timer.Start();
    if (warning_timer.Get() < long_rumble_time) {
      Robot::m_oi.SetOperatorRumbleLeft(0.5);
      Robot::m_oi.SetOperatorRumbleRight(0.5);
    }

    if ((warning_timer.Get() > (rumble_time_alert - dashboard_early_time_alert) && warning_timer.Get() < 0.4 + (rumble_time_alert - dashboard_early_time_alert)) || (warning_timer.Get() > 0.8 + (rumble_time_alert - dashboard_early_time_alert) && warning_timer.Get() < 1.2 + (rumble_time_alert - dashboard_early_time_alert))) {
      frc::SmartDashboard::PutBoolean("Warnings", true);
    } else if (warning_timer.Get() > (rumble_time_alert - dashboard_late_time_alert) && warning_timer.Get() < (rumble_time_alert - dashboard_late_time_alert) + 1.6 && fmod(warning_timer.Get() - (rumble_time_alert - dashboard_late_time_alert), 0.4) < 0.2) {
      frc::SmartDashboard::PutBoolean("Warnings", true);
    } else {
      frc::SmartDashboard::PutBoolean("Warnings", false);
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool MacroControl::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void MacroControl::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MacroControl::Interrupted() {}
