/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoHatchNearRocket.h"
#include "Robot.h"

AutoHatchNearRocket::AutoHatchNearRocket() {}

// Called just before this Command runs the first time
void AutoHatchNearRocket::Initialize() {
  m_timer.Start();
  m_timer.Reset();
  previous_timer = 0;
  previous_angle = 0;
  previous_distance = 0;
  x_position = 47;
  y_position = 67;
  Robot::m_drivetrain.ResetTime();
  path_timer = 0;
  stage = 0;
  Robot::m_drivetrain.ResetEncoders();
  Robot::m_drivetrain.ResetNavX();
  Robot::m_drivetrain.ResetDistanceIntegral();
  Robot::m_drivetrain.ResetGyroIntegral();
  Robot::m_drivetrain.SetSpeed(0, 0);
  Robot::m_drivetrain.ResetEncoders();
  frc::SmartDashboard::PutNumber("Path Calced", Robot::m_drivetrain.CalculateRawPath(40, -70, -40, -50, 0));
  frc::SmartDashboard::PutNumber("Turn Time", Robot::m_drivetrain.GetPathTime());
}

// Called repeatedly when this Command is scheduled to run
void AutoHatchNearRocket::Execute() {
  switch (stage) {
    case 0:
      if (m_timer.Get() < Robot::m_drivetrain.GetPathTime()) {
        Robot::m_drivetrain.FollowPath(m_timer.Get(), m_timer.Get() - previous_timer);
      } else {
        path_timer = Robot::m_drivetrain.GetPathTime();
        Robot::m_drivetrain.CalculateRawPath(-3.7122344192788589776497389941637, -75.209502827876221459823834184105, 11.25, 0, 0);
        //frc::SmartDashboard::PutNumber("Turn Time", Robot::m_drivetrain.GetPathTime());
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
  x_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 180);
  y_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 180);
  frc::SmartDashboard::PutNumber("X", x_position);
  frc::SmartDashboard::PutNumber("Y", y_position);
  frc::SmartDashboard::PutNumber("stage", stage);
  frc::SmartDashboard::PutNumber("Timer", m_timer.Get());
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
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
