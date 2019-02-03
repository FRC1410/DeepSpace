#include "commands/HatchPickupRotate.h"
#include "Robot.h"

HatchPickupRotate::HatchPickupRotate() {
  Requires(&Robot::m_hatch_pickup);
}

// Called just before this Command runs the first time
void HatchPickupRotate::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HatchPickupRotate::Execute() {
  if (Robot::m_macro_superstructure.GetProfile() == hatch_profile_number) {
    hatch_rotator_input = -Robot::m_oi.GetOperatorAxis(hatch_pickup_rotator_axis, operator_deadzone);
    if (abs(hatch_rotator_input) > 0) {
      Robot::m_hatch_pickup.RotatePickup(hatch_rotator_input);
    }
  }

  frc::SmartDashboard::PutNumber("Rotator input amount", hatch_rotator_input);
}

// Make this return true when this Command no longer needs to run execute()
bool HatchPickupRotate::IsFinished() { return false; }

// Called once after isFinished returns true
void HatchPickupRotate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HatchPickupRotate::Interrupted() {}