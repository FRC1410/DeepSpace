/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoGyroPID.h"
#include "Robot.h"

AutoGyroPID::AutoGyroPID() {}

// Called just before this Command runs the first time
void AutoGyroPID::Initialize() {
  Robot::m_drivetrain.ResetNavX();
  m_timer.Start();
  m_timer.Reset();
  Robot::m_drivetrain.SetSpeed(0, 0);
  Robot::m_drivetrain.ResetGyroIntegral();
}

// Called repeatedly when this Command is scheduled to run
void AutoGyroPID::Execute() {
  PID_value = Robot::m_drivetrain.GetGyroPID(0, m_timer.Get());
  Robot::m_drivetrain.Accelerate(PID_value, -PID_value);
  m_timer.Reset();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoGyroPID::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoGyroPID::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoGyroPID::Interrupted() {}
