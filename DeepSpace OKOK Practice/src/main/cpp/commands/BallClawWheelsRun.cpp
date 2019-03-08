/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

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
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_macro_superstructure.GetProfile() == ball_profile_number) {
      if (Robot::m_elevator.GetHeight() >= elevator_low_ball_height - elevator_deadband) {
        if (Robot::m_oi.GetOperatorButton(5) == false) {
          Robot::m_ball_claw.RunWheels(-Robot::m_oi.GetOperatorAxis(ball_claw_left_outtake_axis), -Robot::m_oi.GetOperatorAxis(ball_claw_right_outtake_axis));
        } else {
          Robot::m_ball_claw.RunWheels(Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis), Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis));
        }
      } else {
        if (Robot::m_ball_claw.GetLimitSwitch() == false)  {
          Robot::m_ball_claw.RunWheels(Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis), Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis));
        } else {
          Robot::m_ball_claw.RunWheels(-Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis), -Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis));
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

    if (rumble_timer.Get() < double_rumble_time || (rumble_timer.Get() > (double_rumble_time * 2) && rumble_timer.Get() < (double_rumble_time * 3))) {
      Robot::m_oi.SetOperatorRumbleLeft(1);
      Robot::m_oi.SetOperatorRumbleRight(1);
    } else {
      Robot::m_oi.SetOperatorRumbleLeft(0);
      Robot::m_oi.SetOperatorRumbleRight(0);
    }
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