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
        Robot::m_macro_superstructure.RunLEDs(hatch_color);
        break;
      case ball_profile_number:
        Robot::m_macro_superstructure.RunLEDs(cargo_color);
        break;
      case climber_profile_number:
        Robot::m_macro_superstructure.RunLEDs(climber_color);
        break;
    }
  } else {
    Robot::m_macro_superstructure.RunLEDs(reset_mechanisms_color);
  }
  
  frc::SmartDashboard::PutNumber("Operator Profile", Robot::m_macro_superstructure.GetProfile());
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
