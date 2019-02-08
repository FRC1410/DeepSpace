#include "commands/ClimberExtend.h"
#include "Robot.h"
#include "RobotMap.h"

ClimberExtend::ClimberExtend() {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_climber);
}

// Called just before this Command runs the first time
void ClimberExtend::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimberExtend::Execute() {
  if (Robot::m_macro_superstructure.GetReset() == false) {
    if (Robot::m_macro_superstructure.GetProfile() == climber_profile_number) {
      if (Robot::m_oi.GetOperatorButton(climber_front_button) == true) {
      	if (front_button_was_pressed == false) {
          if (front_extended == false) {
      	    Robot::m_climber.ExtendFront();
            front_extended = true;
  		    } else {
            Robot::m_climber.RetractFront();
            front_extended = false;
  	   	  }
  		  }
  	    front_button_was_pressed = true;
  	  } else {  
  	    front_button_was_pressed = false;
  	  }
      if (Robot::m_oi.GetOperatorButton(climber_back_button) == true) {
        if (back_button_was_pressed == false) {
          if (back_extended == false) {
            Robot::m_climber.ExtendBack();
            back_extended = true;
          } else {
            Robot::m_climber.RetractBack();
            back_extended = false;
          }
        }
  	  	back_button_was_pressed = true;
      } else {  
  	  	back_button_was_pressed = false;
      }
    }
  } else {
    Robot::m_climber.RetractFront();
    front_extended = false;
    Robot::m_climber.RetractBack();
    back_extended = false;
  }
  
  frc::SmartDashboard::PutBoolean("Front Extended", front_extended);
  frc::SmartDashboard::PutBoolean("Back Extended", back_extended);
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