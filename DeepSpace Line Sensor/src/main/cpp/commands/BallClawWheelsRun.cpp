#include "commands/BallClawWheelsRun.h"
#include "Robot.h"

BallClawWheelsRun::BallClawWheelsRun() {
  Requires(&Robot::m_ball_claw);
}

// Called just before this Command runs the first time
void BallClawWheelsRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallClawWheelsRun::Execute() {
  if (Robot::m_oi.GetDriverButton(ball_claw_intake_button) || Robot::m_oi.GetDriverButton(ball_both_intakes_button)) {
    Robot::m_ball_claw.RunWheels(1);
  } else if (Robot::m_oi.GetDriverButton(ball_claw_outtake_button) || Robot::m_oi.GetDriverButton(ball_both_outtakes_button)) {
    Robot::m_ball_claw.RunWheels(-1);
  } else {
    Robot::m_ball_claw.RunWheels(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool BallClawWheelsRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void BallClawWheelsRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallClawWheelsRun::Interrupted() {}
