/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BallWheelsRun.h"
#include "Robot.h"

BallWheelsRun::BallWheelsRun() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void BallWheelsRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallWheelsRun::Execute() {
  if (Robot::m_oi.GetDriverButton(ball_claw_intake_button)) {
    Robot::m_ball_claw.RunWheels(1);
  } else if (Robot::m_oi.GetDriverButton(ball_claw_outtake_button)) {
    Robot::m_ball_claw.RunWheels(-1);
  } else {
    Robot::m_ball_claw.RunWheels(0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool BallWheelsRun::IsFinished() { return false; }

// Called once after isFinished returns true
void BallWheelsRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallWheelsRun::Interrupted() {}
