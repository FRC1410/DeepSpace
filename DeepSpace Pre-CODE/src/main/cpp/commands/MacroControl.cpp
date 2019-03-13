/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
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

  limit_switch_time = 0;
  failure_time = -1;

  failed_before = false;
  switch_was_true = false;
}

// Called repeatedly when this Command is scheduled to run
void MacroControl::Execute() {
  Robot::m_macro_superstructure.SetProfile(Robot::m_oi.GetOperatorDPad());
  if (Robot::m_macro_superstructure.GetReset() == false) {
    switch (Robot::m_macro_superstructure.GetProfile()) {
      case hatch_profile_number:
        Robot::m_macro_superstructure.SetLEDs(hatch_color);
        break;
      case ball_profile_number:
        if (Robot::m_ball_claw.GetLimitSwitch() == true) {
          if (switch_was_true == false) {
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
        Robot::m_macro_superstructure.SetLEDs(climber_color);
        break;
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

  if(compressor_triggered == true) {
    Robot::m_macro_superstructure.SetCompressor(1);
    if(Robot::m_macro_superstructure.GetPressure() > compressor_high_thresh) {
      compressor_triggered = false;
    }
  } else {
    Robot::m_macro_superstructure.SetCompressor(0);
  }

  if((Robot::m_macro_superstructure.GetPressure() < compressor_low_thresh) || (Robot::m_oi.GetOperatorButton(toggle_compressor_button) == true)) {
    compressor_triggered = true;
  }
  
  frc::SmartDashboard::PutNumber("Operator Profile", Robot::m_macro_superstructure.GetProfile());
  frc::SmartDashboard::PutNumber("Pressure", Robot::m_macro_superstructure.GetPressure());
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
