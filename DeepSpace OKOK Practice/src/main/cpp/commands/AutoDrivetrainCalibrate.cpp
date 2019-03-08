/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoDrivetrainCalibrate.h"
#include "Robot.h"

AutoDrivetrainCalibrate::AutoDrivetrainCalibrate() {}

// Called just before this Command runs the first time
void AutoDrivetrainCalibrate::Initialize() {
  m_timer.Start();
  m_timer.Reset();
  stage = 0;
  counter = 0;
  previous_timer = 0;
  average_PID = 0;
  for (int x = 0; x < (sizeof(dists) / 8); x++) {
    dists[x] = 0;
  }
  Robot::m_drivetrain.ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void AutoDrivetrainCalibrate::Execute() {
  switch (stage) {
    case 0:
      if (dists[9] - dists[0] < 0.4) {
        counter++;
      } else {
        stage = 1;
        m_timer.Reset();
      }
      Robot::m_drivetrain.SetSpeed(floor(counter / 10) / 100, floor(counter / 10) / 100);
      for (int x = 0; x < (sizeof(dists) / 8) - 1; x++) {
        dists[x] = dists[x + 1];
      }
      dists[9] = Robot::m_drivetrain.GetDistance();
      break;
    case 1:
      if (m_timer.Get() > 0.5) {
        stage_distance = Robot::m_drivetrain.GetDistance();
        m_timer.Reset();
        stage = 2;
      }
      break;
    case 2:
      if (m_timer.Get() > 1) {
        speed = (Robot::m_drivetrain.GetDistance() - stage_distance) / m_timer.Get();
        Robot::m_drivetrain.SetSpeed(floor(counter / 10) / 100 + 0.2, floor(counter / 10) / 100 + 0.2);
        m_timer.Reset();
        stage = 3;
      }
      break;
    case 3:
      if (m_timer.Get() > 0.5) {
        stage_distance = Robot::m_drivetrain.GetDistance();
        m_timer.Reset();
        stage = 4;
      }
      break;
    case 4:
      if (m_timer.Get() > 1) {
        calculated_friction = (floor(counter / 10) / 100) - ((0.2 * speed) / ((Robot::m_drivetrain.GetDistance() - stage_distance) / m_timer.Get()));
        frc::SmartDashboard::PutNumber("Friction", calculated_friction);
        Robot::m_drivetrain.SetSpeed(0, 0);
        m_timer.Reset();
        stage = 5;
      }
      break;
    case 5:
      if (m_timer.Get() > 0.5) {
        Robot::m_drivetrain.SetSpeed(-calculated_friction - 0.2, -calculated_friction - 0.2);
        stage = 6;
      }
      break;
    case 6:
      if (Robot::m_drivetrain.GetDistance() < 2) {
        Robot::m_drivetrain.SetSpeed(0, 0);
        m_timer.Reset();
        stage = 7;
      }
      break;
    case 7:
      if (m_timer.Get() > 0.5) {
        m_timer.Reset();
        stage_distance = Robot::m_drivetrain.GetDistance();
        stage = 8;
      }
      break;
    case 8:
      if (m_timer.Get() < 1) {
        Robot::m_drivetrain.SetSpeed(m_timer.Get(), m_timer.Get());
      } else {
        Robot::m_drivetrain.SetSpeed(1, 1);
        acceleration_distance = Robot::m_drivetrain.GetDistance() - stage_distance;
        m_timer.Reset();
        stage = 9;
      }
      break;
    case 9:
      if (m_timer.Get() > 1.5) {
        m_timer.Reset();
        stage_distance = Robot::m_drivetrain.GetDistance();
        Robot::m_drivetrain.ResetNavX(0);
        stage = 10;
      }
      break;
    case 10:
      if (Robot::m_drivetrain.GetDistance() + acceleration_distance > 200) {
        speed = (Robot::m_drivetrain.GetDistance() - stage_distance) / m_timer.Get();
        average_PID = average_PID / m_timer.Get();
        frc::SmartDashboard::PutNumber("Drivetrain PID", average_PID);
        frc::SmartDashboard::PutNumber("Max Speed", speed);
        m_timer.Reset();
        stage = 11;
      } else {
        PID = Robot::m_drivetrain.GetGyroPID(0, m_timer.Get() - previous_timer);
        average_PID += (PID * (m_timer.Get() - previous_timer));
        Robot::m_drivetrain.SetSpeed(1 + PID, 1 - PID);
      }
      previous_timer = m_timer.Get();
      break;
    case 11:
      if (m_timer.Get() < 1) {
        Robot::m_drivetrain.SetSpeed(1 - m_timer.Get(), 1 - m_timer.Get());
      } else {
        Robot::m_drivetrain.SetSpeed(0, 0);
        m_timer.Reset();
        stage = 12;
      }
      break;
    case 12:
      if (m_timer.Get() > 0.5) {
        m_timer.Reset();
        stage = 13;
      }
      break;
    case 13:
      if (m_timer.Get() < 1) {
        Robot::m_drivetrain.SetSpeed(m_timer.Get(), -m_timer.Get());
      } else {
        Robot::m_drivetrain.SetSpeed(1, -1);
        m_timer.Reset();
        stage = 14;
      }
      break;
    case 14:
      if (m_timer.Get() > 5) {
        m_timer.Reset();
        stage = 15;
        stage_angle = Robot::m_drivetrain.GetAngle();
      }
      break;
    case 15:
      if (m_timer.Get() > 5) {
        frc::SmartDashboard::PutNumber("Driftiness", (Robot::m_drivetrain.GetAngle() - stage_angle) * (pi / 180) * drivetrain_radius / (m_timer.Get() * speed * 2));
        m_timer.Reset();
        stage = 16;
      } else {
        Robot::m_drivetrain.SetSpeed(1, -1);
      }
      break;
    case 16:
      if (m_timer.Get() < 1) {
        Robot::m_drivetrain.SetSpeed(1 - m_timer.Get(), m_timer.Get() - 1);
      } else {
        Robot::m_drivetrain.SetSpeed(0, 0);
      }
      break;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrivetrainCalibrate::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    return true;
  } else {
    return false; 
  }
}

// Called once after isFinished returns true
void AutoDrivetrainCalibrate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrivetrainCalibrate::Interrupted() {}