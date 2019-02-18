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
  Robot::m_macro_superstructure.StartCompressor();
}

// Called repeatedly when this Command is scheduled to run
void MacroControl::Execute() {
  Robot::m_macro_superstructure.SetProfile(Robot::m_oi.GetOperatorDPad());
  if (Robot::m_macro_superstructure.GetReset() == false) {
    switch (Robot::m_macro_superstructure.GetProfile()) {
      case hatch_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(hatch_color);
        Robot::m_macro_superstructure.SetRightLEDs(hatch_color);
        break;
      case ball_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(ball_color);
        Robot::m_macro_superstructure.SetRightLEDs(ball_color);
        break;
      case climber_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(climber_color);
        Robot::m_macro_superstructure.SetRightLEDs(climber_color);
        break;
    }
  } else {
    Robot::m_macro_superstructure.SetLeftLEDs(reset_mechanisms_color);
    Robot::m_macro_superstructure.SetRightLEDs(reset_mechanisms_color);
  }
  if (Robot::m_oi.GetHumanPlayerButton(5) == true) {
    if (l_was_pressed == false) {
      if (color > -0.98) {
        color -= 0.02;
      }
    }
  	l_was_pressed = true;
  } else {  
    l_was_pressed = false;
  }
  if (Robot::m_oi.GetHumanPlayerButton(6) == true) {
    if (r_was_pressed == false) {
      if (color < 0.98) {
        color += 0.02;
      }
    }
  	r_was_pressed = true;
  } else {  
    r_was_pressed = false;
  }
  if (Robot::m_oi.GetHumanPlayerAxis(0) != 0 || Robot::m_oi.GetHumanPlayerAxis(1) != 0 || Robot::m_oi.GetHumanPlayerAxis(4) != 0 || Robot::m_oi.GetHumanPlayerAxis(5) != 0) {
    Robot::m_macro_superstructure.SetLeftLEDs(color);
    Robot::m_macro_superstructure.SetRightLEDs(color);
    frc::SmartDashboard::PutNumber("Color", floor(color * 100) / 100);
  }

  if (Robot::m_oi.GetOperatorButton(toggle_compressor_button) == true) {
    if (button_was_pressed == false) {
      if (compressing == false) {
        Robot::m_macro_superstructure.StartCompressor();
        compressing = true;
      } else {
        Robot::m_macro_superstructure.StopCompressor();
        compressing = false;
      }
    }
  	button_was_pressed = true;
  } else {  
    button_was_pressed = false;
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
