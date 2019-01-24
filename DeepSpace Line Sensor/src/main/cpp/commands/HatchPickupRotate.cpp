#include "commands/HatchPickupRotate.h"
#include "Robot.h"

HatchPickupRotate::HatchPickupRotate() {
  Requires(&Robot::m_hatch_pickup);
}

// Called just before this Command runs the first time
void HatchPickupRotate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchPickupRotate::Execute() {
  left_trigger_amount = Robot::m_oi.GetDriverAxis(left_trigger, 0);
  right_trigger_amount = Robot::m_oi.GetDriverAxis(right_trigger, 0);

  Robot::m_hatch_pickup.RotatePickup(right_trigger_amount - left_trigger_amount);

  frc::SmartDashboard::PutNumber("Trigger amount", right_trigger_amount - left_trigger_amount);
}

// Make this return true when this Command no longer needs to run execute()
bool HatchPickupRotate::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchPickupRotate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchPickupRotate::Interrupted() {}
