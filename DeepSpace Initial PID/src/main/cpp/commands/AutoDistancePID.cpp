#include "commands/AutoDistancePID.h"
#include "Robot.h"

AutoDistancePID::AutoDistancePID() {}

// Called just before this Command runs the first time
void AutoDistancePID::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoDistancePID::Execute() {
  
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDistancePID::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoDistancePID::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDistancePID::Interrupted() {}
