#include "commands/AutoElevatorCalibrate.h"
#include "Robot.h"

AutoElevatorCalibrate::AutoElevatorCalibrate() {}

// Called just before this Command runs the first time
void AutoElevatorCalibrate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoElevatorCalibrate::Execute() {
  
}
      
// Make this return true when this Command no longer needs to run execute()
bool AutoElevatorCalibrate::IsFinished() {
  return false; 
}

// Called once after isFinished returns true
void AutoElevatorCalibrate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoElevatorCalibrate::Interrupted() {}
