#include "commands/MacroControl.h"
#include "Robot.h"

MacroControl::MacroControl() {
  Requires(&Robot::m_macro_superstructure);
}

// Called just before this Command runs the first time
void MacroControl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void MacroControl::Execute() {
  Robot::m_macro_superstructure.SetProfile(Robot::m_oi.GetOperatorDPad());
  if (Robot::m_macro_superstructure.GetReset() == false) {
    switch (Robot::m_macro_superstructure.GetProfile()) {
      case hatch_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(hatch_color);
        break;
      case ball_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(ball_color);
        break;
      case climber_profile_number:
        Robot::m_macro_superstructure.SetLeftLEDs(climber_color);
        break;
    }
  } else {
    Robot::m_macro_superstructure.SetLeftLEDs(reset_mechanisms_color);
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
