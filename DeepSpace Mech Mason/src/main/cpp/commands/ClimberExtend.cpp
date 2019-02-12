#include "commands/ClimberExtend.h"
#include "Robot.h"
ClimberExtend::ClimberExtend() {
  Requires(&Robot::m_climber);
}

// Called just before this Command runs the first time
void ClimberExtend::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberExtend::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_macro_superstructure.GetProfile() == climber_profile_number) {
      if (Robot::m_oi.GetOperatorButton(climber_front_button) == true) {
      	if (front_button_was_pressed == false) {
          if (Robot::m_climber.GetFrontState() == false) {
      	    Robot::m_climber.ExtendFront();
          } else {
            Robot::m_climber.RetractFront();
          }
        }
  	    front_button_was_pressed = true;
  	  } else {  
  	    front_button_was_pressed = false;
  	  }
      if (Robot::m_oi.GetOperatorButton(climber_back_button) == true) {
        if (back_button_was_pressed == false) {
          if (Robot::m_climber.GetBackState() == false) {
            Robot::m_climber.ExtendBack();
          } else {
            Robot::m_climber.RetractBack();
          }
        }
        back_button_was_pressed = true;
      } else {  
        back_button_was_pressed = false;
      }
    }
    if (Robot::m_macro_superstructure.GetReset() == true) {
      Robot::m_climber.RetractFront();
      Robot::m_climber.RetractBack();
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberExtend::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void ClimberExtend::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberExtend::Interrupted() {}