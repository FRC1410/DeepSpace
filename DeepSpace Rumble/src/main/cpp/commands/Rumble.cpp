/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Rumble.h"
#include "Robot.h"
#include "RobotMap.h"
#include "OI.h"

Rumble::Rumble() {
  Requires(&Robot::m_ball_intake);
}

// Called just before this Command runs the first time
void Rumble::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Rumble::Execute() {
  Robot::m_oi.SetOperatorRumbleLeft(Robot::m_oi.GetOperatorAxis(2, 0));
  Robot::m_oi.SetOperatorRumbleRight(Robot::m_oi.GetOperatorAxis(3, 0));
}

// Make this return true when this Command no longer needs to run execute()
bool Rumble::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void Rumble::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rumble::Interrupted() {}
