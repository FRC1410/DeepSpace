#include "commands/Drive.h"
#include "Robot.h"
#include "OI.h"

Drive::Drive() {}

// Called just before this Command runs the first time
void Drive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  left_stick_amount = -Robot::m_oi.GetDriverAxis(1);
  right_stick_amount = -Robot::m_oi.GetDriverAxis(5);
  Robot::m_drivetrain.TankDrive(left_stick_amount, right_stick_amount);
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}
