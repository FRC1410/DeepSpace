#include "commands/BallClawWheelsRun.h"
#include "Robot.h"
#include "OI.h"

BallClawWheelsRun::BallClawWheelsRun() {
  Requires(&Robot::m_ball_claw);
}

// Called just before this Command runs the first time
void BallClawWheelsRun::Initialize() {
  rumble_timer.Start();
  rumble_timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void BallClawWheelsRun::Execute() {
  if (Robot::m_macro_superstructure.GetProfile() == 1) {
    if (Robot::m_elevator.GetHeight() > 20) {
      Robot::m_ball_claw.RunLeftWheels(-Robot::m_oi.GetOperatorAxis(ball_claw_left_outtake_axis, 0));
      Robot::m_ball_claw.RunRightWheels(-Robot::m_oi.GetOperatorAxis(ball_claw_right_outtake_axis, 0));
    } else {
      if (Robot::m_ball_claw.GetLimitSwitch() == false)  {
        Robot::m_ball_claw.RunWheels(Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis, 0) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis, 0));
      } else {
        Robot::m_ball_claw.RunWheels(-Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis, 0));
      }
    }
  }

  if (Robot::m_ball_claw.GetLimitSwitch() == true) {
    if (switch_was_true == false) {
      rumble_timer.Reset();
    }
    switch_was_true = true;
  } else {
    switch_was_true = false;
  }

  if (rumble_timer.Get() < 0.15 || (rumble_timer.Get() > 0.3 && rumble_timer.Get() < 0.45)) {
    Robot::m_oi.SetOperatorRumbleLeft(1);
    Robot::m_oi.SetOperatorRumbleRight(1);
  } else {
    Robot::m_oi.SetOperatorRumbleLeft(0);
    Robot::m_oi.SetOperatorRumbleRight(0);
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