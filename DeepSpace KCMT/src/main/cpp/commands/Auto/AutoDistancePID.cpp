/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoDistancePID.h"
#include "Robot.h"

AutoDistancePID::AutoDistancePID() {}

// Called just before this Command runs the first time
void AutoDistancePID::Initialize() {
  Robot::m_drivetrain.ResetDistanceIntegral();

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
}

// Called repeatedly when this Command is scheduled to run
void AutoDistancePID::Execute() {
  PID_value = Robot::m_drivetrain.GetDistancePID(100 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
  Robot::m_drivetrain.Accelerate(PID_value, PID_value, m_timer.Get() - previous_timer);

  previous_timer = m_timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDistancePID::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoDistancePID::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDistancePID::Interrupted() {}