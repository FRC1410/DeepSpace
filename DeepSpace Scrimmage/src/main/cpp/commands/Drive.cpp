/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Drive.h"
#include "Robot.h"

Drive::Drive() {
  Requires(&Robot::m_drivetrain);
}

// Called just before this Command runs the first time
void Drive::Initialize() {
  Robot::m_drivetrain.ResetNavX();
  Robot::m_drivetrain.ResetEncoders();
  rumble_timer.Start();
  rumble_timer.Reset();

  timer.Start();
  timer.Reset();

  x_position = 0;
  y_position = 0;

  invert_driving = true;
  Robot::m_drivetrain.SetSpeed(0, 0);
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_oi.GetDriverButton(line_align_button) == true) {
      if (Robot::m_drivetrain.GetMiddleSensor() == true) {
        if (Robot::m_drivetrain.GetLeftSensor() == true) {
          if (Robot::m_drivetrain.GetRightSensor() == true) {
            invert_driving = true;
            goto driver_control;
          } else {
            Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput(), Robot::m_oi.GetAverageDriverInput() * 0.6);
          }
        } else {
          if (Robot::m_drivetrain.GetRightSensor() == true) {
            Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput() * 0.6, Robot::m_oi.GetAverageDriverInput());
          } else {
            Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput(), Robot::m_oi.GetAverageDriverInput());
          }
        }
      } else {
        if (Robot::m_drivetrain.GetLeftSensor() == true) {
          if (Robot::m_drivetrain.GetRightSensor() == true) {
            invert_driving = true;
            goto driver_control;
          } else {
            Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput(), Robot::m_oi.GetAverageDriverInput() * 0.1);
          }
        } else {
          if (Robot::m_drivetrain.GetRightSensor() == true) {
            Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput() * 0.1, Robot::m_oi.GetAverageDriverInput());
          } else {
            invert_driving = true;
            goto driver_control;
          }
        }
      }
    } else {
      driver_control:
        if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
          if (invert_button_was_pressed == false) {
            rumble_timer.Reset();
            if (invert_driving == false) {
              invert_driving = true;
            } else {
              invert_driving = false;
            }
          }
          invert_button_was_pressed = true;
        } else {
          invert_button_was_pressed = false;
        }

        left_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_left_axis);
        right_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_right_axis);

        if (Robot::m_drivetrain.GetLeftSensor() == true || Robot::m_drivetrain.GetMiddleSensor() == true || Robot::m_drivetrain.GetRightSensor() == true) {
          Robot::m_oi.SetDriverRumbleLeft(0.5);
          Robot::m_oi.SetDriverRumbleRight(0.5);
        } else {
          if (invert_driving == false) {
            if (rumble_timer.Get() < 0.25) {
              Robot::m_oi.SetDriverRumbleLeft(1);
              Robot::m_oi.SetDriverRumbleRight(1);
            } else {
              Robot::m_oi.SetDriverRumbleLeft(0);
              Robot::m_oi.SetDriverRumbleRight(0);
            }
          } else {
            if (rumble_timer.Get() < 0.15 || (rumble_timer.Get() > 0.3 && rumble_timer.Get() < 0.45)) {
              Robot::m_oi.SetDriverRumbleLeft(1);
              Robot::m_oi.SetDriverRumbleRight(1);
            } else {
              Robot::m_oi.SetDriverRumbleLeft(0);
              Robot::m_oi.SetDriverRumbleRight(0);
            }
          }
        }
        if (invert_driving == false) {
          Robot::m_drivetrain.SetSpeed(left_stick_amount, right_stick_amount);    
        } else {
          Robot::m_drivetrain.SetSpeed(-right_stick_amount, -left_stick_amount);
        }
    }
  }

  x_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * sin(Robot::m_drivetrain.GetAngle() * pi / 180);
  y_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * cos(Robot::m_drivetrain.GetAngle() * pi / 180);

  frc::SmartDashboard::PutNumber("X Position", x_position);
  frc::SmartDashboard::PutNumber("Y Position", y_position);

  frc::SmartDashboard::PutNumber("NavX Value", Robot::m_drivetrain.GetAngle());

  frc::SmartDashboard::PutBoolean("Left Tape Sensor", Robot::m_drivetrain.GetLeftSensor());
  frc::SmartDashboard::PutBoolean("Middle Tape Sensor", Robot::m_drivetrain.GetMiddleSensor());
  frc::SmartDashboard::PutBoolean("Right Tape Sensor", Robot::m_drivetrain.GetRightSensor());
  frc::SmartDashboard::PutBoolean("Invert Driving", invert_driving);

  timer.Reset();
  previous_distance = Robot::m_drivetrain.GetDistance();
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}