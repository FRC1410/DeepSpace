#include "commands/HatchWheelsRun.h"
#include "Robot.h"

HatchWheelsRun::HatchWheelsRun() {}

// Called just before this Command runs the first time
void HatchWheelsRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchWheelsRun::Execute() {
  if (Robot::m_oi.GetDriverButton(hatch_intake_button)) {
    Robot::m_hatch_intake.RunWheels(1);
  } else if (Robot::m_oi.GetDriverButton(hatch_outtake_button)) {
    Robot::m_hatch_intake.RunWheels(-1);
  } else {
    Robot::m_hatch_intake.RunWheels(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool HatchWheelsRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void HatchWheelsRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchWheelsRun::Interrupted() {}