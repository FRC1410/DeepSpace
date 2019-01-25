#include "commands/BallRollerRun.h"
#include "Robot.h"

BallRollerRun::BallRollerRun() {
  Requires(&Robot::m_ball_roller);
}

// Called just before this Command runs the first time
void BallRollerRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallRollerRun::Execute() {
  if (Robot::m_oi.GetDriverButton(ball_roller_intake_button) || Robot::m_oi.GetDriverButton(ball_both_intakes_button)) {
    Robot::m_ball_roller.RunIntake(1);
  } else if (Robot::m_oi.GetDriverButton(ball_roller_outtake_button) || Robot::m_oi.GetDriverButton(ball_both_outtakes_button)) {
    Robot::m_ball_roller.RunIntake(-1);
  } else {
    Robot::m_ball_roller.RunIntake(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool BallRollerRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void BallRollerRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallRollerRun::Interrupted() {}
