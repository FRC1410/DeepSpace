#include "commands/HatchStickActuate.h"
#include "Robot.h"

HatchStickActuate::HatchStickActuate() {
  Requires(&Robot::m_hatch_stick);
}

// Called just before this Command runs the first time
void HatchStickActuate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchStickActuate::Execute() {
  if (Robot::m_macro_superstructure.GetReset() == false) {
    if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
      if (Robot::m_oi.GetOperatorButton(hatch_stick_button) == true) {
        if (button_was_pressed == false) {
          if (Robot::m_hatch_stick.GetState() == false) {
            Robot::m_hatch_stick.ExtendStick();
          } else {
            Robot::m_hatch_stick.RetractStick();
     	    }
        }
        button_was_pressed = true;
      } else {  
        button_was_pressed = false;
      }
    }
  } else {
    Robot::m_hatch_stick.RetractStick();
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchStickActuate::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchStickActuate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchStickActuate::Interrupted() {}