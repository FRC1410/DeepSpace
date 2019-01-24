#include "commands/HatchStickActuate.h"
#include "Robot.h"

HatchStickActuate::HatchStickActuate() {
  Requires(&Robot::m_hatch_stick);
}

// Called just before this Command runs the first time
void HatchStickActuate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchStickActuate::Execute() {
  if (Robot::m_oi.GetDriverButton(hatch_stick_button)) {
		if (select_was_pressed == false) {
			if (stick_extended == false) {
        Robot::m_hatch_stick.ExtendStick();
        stick_extended = true;
			} else {
        Robot::m_hatch_stick.RetractStick();
        stick_extended = false;
			}
		}
		select_was_pressed = true;
	} else {
	  select_was_pressed = false;
	}

  if (stick_extended == false) {
    frc::SmartDashboard::PutString("Stick State", "Retracted");
  } else {
    frc::SmartDashboard::PutString("Stick State", "Extended");
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchStickActuate::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchStickActuate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchStickActuate::Interrupted() {}
