#include "Robot.h"
#include "commands/AutoLimelightTargeting.h"

AutoLimelightTargeting::AutoLimelightTargeting() {
  Requires(&Robot::m_drivetrain);
  Requires(&Robot::m_limelight);
}

// Called just before this Command runs the first time
void AutoLimelightTargeting::Initialize() {
  Robot::m_limelight.TurnOnLights();
}

// Called repeatedly when this Command is scheduled to run
void AutoLimelightTargeting::Execute() {
  if (Robot::m_limelight.GetTarget() == true) {
    Robot::m_drivetrain.TankDrive(Robot::m_limelight.GetTargetX()/50 + (Robot::m_limelight.GetTargetArea() - 1) / 2, -Robot::m_limelight.GetTargetX()/50 + (Robot::m_limelight.GetTargetArea() - 1) / 2);
  } else {
    Robot::m_drivetrain.TankDrive(0, 0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoLimelightTargeting::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoLimelightTargeting::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoLimelightTargeting::Interrupted() {}
