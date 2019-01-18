/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BallBothIntakes.h"
#include "Robot.h"
#include "RobotMap.h"
#include "OI.h"

BallBothIntakes::BallBothIntakes() {
  Requires(&Robot::m_ball_claw);
  Requires(&Robot::m_ball_intake);
}

// Called just before this Command runs the first time
void BallBothIntakes::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallBothIntakes::Execute() {
  left_trigger_amount = Robot::m_oi.GetDriverAxis(left_trigger, 0);
  right_trigger_amount = Robot::m_oi.GetDriverAxis(right_trigger, 0);

  Robot::m_ball_claw.RunWheels(right_trigger_amount - left_trigger_amount);
  Robot::m_ball_intake.RunIntake(right_trigger_amount - left_trigger_amount);
}

bool BallBothIntakes::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void BallBothIntakes::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallBothIntakes::Interrupted() {}
