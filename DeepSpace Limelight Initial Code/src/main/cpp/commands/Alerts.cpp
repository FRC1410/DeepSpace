#include "commands/Alerts.h"
#include "Robot.h"

Alerts::Alerts() {}

// Called just before this Command runs the first time
void Alerts::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Alerts::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Alerts::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void Alerts::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Alerts::Interrupted() {}
