#include "commands/BallIntakeRun.h"
#include "Robot.h"
#include "OI.h"


BallIntakeRun::BallIntakeRun() {}

// Called just before this Command runs the first time
void BallIntakeRun::Initialize() {}


// Called repeatedly when this Command is scheduled to run
void BallIntakeRun::Execute() {
  if (Robot::m_oi.GetDriverButton(ball_roller_intake_button)) {
    Robot::m_ball_intake.RunIntake(1);
  } else if (Robot::m_oi.GetDriverButton(ball_roller_outtake_button)) {
    Robot::m_ball_intake.RunIntake(-1);
  } else {
    Robot::m_ball_intake.RunIntake(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool BallIntakeRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void BallIntakeRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallIntakeRun::Interrupted() {}
