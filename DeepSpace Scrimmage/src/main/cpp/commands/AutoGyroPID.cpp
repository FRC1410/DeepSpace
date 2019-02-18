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
  timer.Start();
  timer.Reset();
  Robot::m_drivetrain.ResetNavX();
  Robot::m_drivetrain.ResetGyroIntegral();
}

// Called repeatedly when this Command is scheduled to run
void AutoGyroPID::Execute() {
  frc::SmartDashboard::PutNumber("NavX Value", Robot::m_drivetrain.GetAngle());
  PID = Robot::m_drivetrain.GetGyroPID(0, timer.Get() - previous_timer);
  if (timer.Get() < 0.5) {
    Robot::m_drivetrain.Accelerate(1 + PID, 1 - PID);
  } else {
    frc::SmartDashboard::PutNumber("PID", PID);
    Robot::m_drivetrain.SetSpeed(1 + PID, 1 - PID);
  }
  previous_timer = timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoGyroPID::IsFinished() { 
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    return true;
  } else {
    return false; 
  }
}

// Called once after isFinished returns true
void AutoGyroPID::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoGyroPID::Interrupted() {}
