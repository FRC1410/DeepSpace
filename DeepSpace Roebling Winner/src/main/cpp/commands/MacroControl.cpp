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
  compressor_triggered = true;
  Robot::m_macro_superstructure.SetCompressor(true);

  cycle_negative_was_pressed = false;
  cycle_positive_was_pressed = true;

  m_timer.Reset();
  m_timer.Start();

  rumble_timer.Reset();
  rumble_timer.Start();

  warning_timer.Reset();
  warning_timer.Stop();
}

// Called repeatedly when this Command is scheduled to run
void MacroControl::Execute() {
  Robot::m_macro_superstructure.SetProfile(Robot::m_oi.GetOperatorDPad());

  if (Robot::m_macro_superstructure.GetReset() == false) {
    if (Robot::m_limelight.GetPipeline() == limelight_driver_pipeline) {
      if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
        Robot::m_macro_superstructure.SetLEDs(hatch_color);
      } else {
        if (Robot::m_ball_claw.GetLimitSwitch() == true) {
          if (switch_was_true == false) {
            rumble_timer.Reset();
          }
          switch_was_true = true;
        } else {
          switch_was_true = false;
        }

        if (rumble_timer.Get() < (blinking_LED_time * 5) && fmod(rumble_timer.Get(), blinking_LED_time * 2) < blinking_LED_time) {
          Robot::m_macro_superstructure.SetLEDs(ball_acquired_color);
        } else {
          Robot::m_macro_superstructure.SetLEDs(ball_color);
        }
      }
    } else {
      Robot::m_macro_superstructure.SetLEDs(vision_targeting_color);
    }
  } else {
    Robot::m_macro_superstructure.SetLEDs(reset_mechanisms_color);
  }

  if (Robot::m_oi.GetHumanPlayerButton(LED_cycle_negative_button) == true) {
    if (cycle_negative_was_pressed == false) {
      if (color > -0.98) {
        color -= 0.02;
      }
    }
  	cycle_negative_was_pressed = true;
  } else {  
    cycle_negative_was_pressed = false;
  }

  if (Robot::m_oi.GetHumanPlayerButton(LED_cycle_positive_button) == true) {
    if (cycle_positive_was_pressed == false) {
      if (color < 0.98) {
        color += 0.02;
      }
    }
  	cycle_positive_was_pressed = true;
  } else {  
    cycle_positive_was_pressed = false;
  }

  if (Robot::m_oi.GetHumanPlayerAxis(0) != 0 || Robot::m_oi.GetHumanPlayerAxis(1) != 0 || Robot::m_oi.GetHumanPlayerAxis(4) != 0 || Robot::m_oi.GetHumanPlayerAxis(5) != 0) {
    Robot::m_macro_superstructure.SetLEDs(color);
  }

  /*if (compressor_triggered == true) {
    Robot::m_macro_superstructure.SetCompressor(true);

    if (Robot::m_macro_superstructure.GetPressure() > compressor_high_thresh) {
      compressor_triggered = false;
    }
  } else {
    Robot::m_macro_superstructure.SetCompressor(false);
  }

  if ((Robot::m_macro_superstructure.GetPressure() < compressor_low_thresh) || (Robot::m_oi.GetOperatorButton(toggle_compressor_button) == true) || (Robot::m_macro_superstructure.GetFMSAuto() == true)) {
    compressor_triggered = true;
  }
  
  if (rumble_timer.Get() < double_rumble_time || (rumble_timer.Get() > (double_rumble_time * 2) && rumble_timer.Get() < (double_rumble_time * 3))) {
    Robot::m_oi.SetOperatorRumble(1, 1);
  } else {
    Robot::m_oi.SetOperatorRumble(0, 0);
  }*/

  if (frc::Timer::GetMatchTime() < rumble_time_alert && frc::Timer::GetMatchTime() > 1 && Robot::m_macro_superstructure.GetFMSAuto() == false) {
    warning_timer.Start();
    if (warning_timer.Get() < long_rumble_time) {
      //Robot::m_oi.SetOperatorRumble(0.5, 0.5);
    }

    if ((warning_timer.Get() > (rumble_time_alert - dashboard_early_time_alert) && warning_timer.Get() < dashboard_slow_blink_time + (rumble_time_alert - dashboard_early_time_alert)) || (warning_timer.Get() > (dashboard_slow_blink_time * 2) + (rumble_time_alert - dashboard_early_time_alert) && warning_timer.Get() < (dashboard_slow_blink_time * 3) + (rumble_time_alert - dashboard_early_time_alert))) {
      Robot::m_macro_superstructure.SetWarnings(true, frc::Timer::GetMatchTime());
    } else if (warning_timer.Get() > (rumble_time_alert - dashboard_late_time_alert) && warning_timer.Get() < (rumble_time_alert - dashboard_late_time_alert) + (dashboard_fast_blink_time * 9) && fmod(warning_timer.Get() - (rumble_time_alert - dashboard_late_time_alert), dashboard_fast_blink_time * 2) < dashboard_fast_blink_time) {
      Robot::m_macro_superstructure.SetWarnings(true, frc::Timer::GetMatchTime());
    } else {
      Robot::m_macro_superstructure.SetWarnings(false, frc::Timer::GetMatchTime());
    }
  } else {
    Robot::m_macro_superstructure.SetWarnings(false, frc::Timer::GetMatchTime());
  }

  if (Robot::m_limelight.GetTargetFound() == true) {
    Robot::m_oi.SetOperatorRumble(0.5, 0.5);
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