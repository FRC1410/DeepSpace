/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Auto/AutoElevatorCalibrate.h"
#include "Robot.h"

AutoElevatorCalibrate::AutoElevatorCalibrate() {}

// Called just before this Command runs the first time
void AutoElevatorCalibrate::Initialize() {
  timer.Start();
  timer.Reset();
  stage = 0;
  counter = 350;
  for (int x = 0; x < (sizeof(revs) / 8); x++) {
    revs[x] = 0;
  }
  previous_timer = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutoElevatorCalibrate::Execute() {
  switch (stage) {
    case 0: 
      if (revs[9] - revs[0] < 0.5) {
        counter++;
      } else {
        stage = 1;
        timer.Reset();
      }
      Robot::m_elevator.RunElevator(floor(counter / 10) / 1000);
      for (int x = 0; x < (sizeof(revs) / 8) - 1; x++) {
        revs[x] = revs[x + 1];
      }
      revs[9] = Robot::m_elevator.GetAverageRevolutions();
      break;
    case 1:
      if (timer.Get() > 0.5) {
        stage_height = Robot::m_elevator.GetAverageRevolutions();
        timer.Reset();
        stage = 2;
      }
      break;
    case 2:
      if (timer.Get() > 1) {
        speed = (Robot::m_elevator.GetAverageRevolutions() - stage_height) / timer.Get();
        Robot::m_elevator.RunElevator(floor(counter / 10) / 1000 + 0.02);
        timer.Reset();
        stage = 3;
      }
      break;
    case 3:
      if (timer.Get() > 0.5) {
        stage_height = Robot::m_elevator.GetAverageRevolutions();
        timer.Reset();
        stage = 4;
      }
      break;
    case 4:
      if (timer.Get() > 1) {
        calculated_strong_gravity = (floor(counter / 10) / 1000) - ((0.02 * speed) / ((Robot::m_elevator.GetAverageRevolutions() - stage_height) / timer.Get()));
        frc::SmartDashboard::PutNumber("Strong Gravity", calculated_strong_gravity);
        stage_height = Robot::m_elevator.GetAverageRevolutions();
        stage = 5;
      }
      break;
    case 5:
      Robot::m_elevator.RunElevator((stage_height - Robot::m_elevator.GetAverageRevolutions()) * 0.03);
      if (timer.Get() > 1.5) {
        timer.Reset();
        previous_timer = 0;
        stage = 6;
      }
      break;
    case 6:
      if (timer.Get() > 1) {
        calculated_weak_gravity = calculated_weak_gravity / timer.Get();
        frc::SmartDashboard::PutNumber("PID Weak Gravity", calculated_weak_gravity);
        Robot::m_elevator.RunElevator(-0.01);
        timer.Reset();
        stage = 7;
      } else {
        calculated_weak_gravity += (stage_height - Robot::m_elevator.GetAverageRevolutions()) * 0.03 * (timer.Get() - previous_timer);
        Robot::m_elevator.RunElevator((stage_height - Robot::m_elevator.GetAverageRevolutions()) * 0.03);
      }
      previous_timer = timer.Get();
      break;
    case 7:
      if (timer.Get() > 0.5) {
        timer.Reset();
        stage_height = Robot::m_elevator.GetAverageRevolutions();
        stage = 8;
      }
      break;
    case 8:
      if (Robot::m_elevator.GetAverageRevolutions() < 1) {
        timer.Reset();
        Robot::m_elevator.RunElevator(0);
        stage = 9;
      }
      break;
    case 9:
      if (timer.Get() > 1) {
        timer.Reset();
        height_error = Robot::m_elevator.GetAverageRevolutions();
        frc::SmartDashboard::PutNumber("Height Error", height_error);
        Robot::m_elevator.ResetEncoders();
        stage = 10;
      }
      break;
    case 10:
      if (Robot::m_elevator.GetAverageRevolutions() < 15) {
        if (timer.Get() < ((1 - calculated_strong_gravity) / 4) + calculated_strong_gravity / 2) {
          Robot::m_elevator.RunElevator(timer.Get() * 2);
        } else {
          Robot::m_elevator.RunElevator(0.5 + calculated_strong_gravity / 2);
          acceleration_distance = Robot::m_elevator.GetAverageRevolutions();
          timer.Reset();
          stage = 11;
        }
      } else {
        Robot::m_elevator.RunElevator(0);
        stage = 14;
      }
      break;
    case 11:
      if (Robot::m_elevator.GetAverageRevolutions() < 30 - acceleration_distance) {
        if (timer.Get() > 0.2) {
          timer.Reset();
          stage = 12;
        }
      } else {
        Robot::m_elevator.RunElevator(0);
        stage = 14;
      }
      break;
    case 12:
      if (Robot::m_elevator.GetAverageRevolutions() > 30 - acceleration_distance) {
        frc::SmartDashboard::PutNumber("Half Speed", (Robot::m_elevator.GetAverageRevolutions() - acceleration_distance) / timer.Get());
        timer.Reset();
        stage = 13;
      }
      break;
    case 13:
      if (timer.Get() < ((1 - calculated_strong_gravity) / 4) + calculated_strong_gravity / 2) {
        Robot::m_elevator.RunElevator((0.5 + calculated_strong_gravity / 2) - (timer.Get() * 2));
      } else {
        Robot::m_elevator.RunElevator(calculated_weak_gravity);
        frc::SmartDashboard::PutNumber("Elevator Revolutions", Robot::m_elevator.GetAverageRevolutions());
      }
      break;
    default:
      Robot::m_elevator.RunElevator(0);
  }
}
      
// Make this return true when this Command no longer needs to run execute()
bool AutoElevatorCalibrate::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoElevatorCalibrate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoElevatorCalibrate::Interrupted() {}