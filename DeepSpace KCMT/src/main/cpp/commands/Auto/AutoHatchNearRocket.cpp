/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoHatchNearRocket.h"
#include "Robot.h"

AutoHatchNearRocket::AutoHatchNearRocket() {}

// Called just before this Command runs the first time
void AutoHatchNearRocket::Initialize() {
  stage = 0;

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
  path_timer = 0;

  Robot::m_drivetrain.CalculateRawPath(40 * Robot::m_macro_superstructure.GetInvertedAuto(), -70, -40 * Robot::m_macro_superstructure.GetInvertedAuto(), -50, 0);
}

// Called repeatedly when this Command is scheduled to run
void AutoHatchNearRocket::Execute() {
  switch (stage) {
    case 0:
      if (m_timer.Get() < Robot::m_drivetrain.GetPathTime()) {
        Robot::m_drivetrain.FollowPath(m_timer.Get(), m_timer.Get() - previous_timer);
      } else {
        path_timer = Robot::m_drivetrain.GetPathTime();
        Robot::m_drivetrain.CalculateRawPath(-3.7122344192788589776497389941637 * Robot::m_macro_superstructure.GetInvertedAuto(), -75.209502827876221459823834184105, 11.25 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0);
        stage = 1;
      }
      break;
    case 1:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        stage = 2;
      }
      break;
    default:
      Robot::m_drivetrain.SetSpeed(0, 0);
  }

  Robot::m_macro_superstructure.SetStage(stage);
  
  previous_timer = m_timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoHatchNearRocket::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoHatchNearRocket::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoHatchNearRocket::Interrupted() {}