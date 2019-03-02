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
  rumble_timer.Start();
  rumble_timer.Reset();

  timer.Start();
  timer.Reset();

  vision_timer.Start();
  vision_timer.Reset();
  
  rumble_timer2.Start();
  rumble_timer2.Reset();

  x_position = 0;
  y_position = 0;

  invert_driving = true;
  Robot::m_drivetrain.SetSpeed(0, 0);
  Robot::m_drivetrain.ResetEncoders();
  Robot::m_drivetrain.ResetNavX();
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_y = y_position;
  vision_align_was_pressed = false;
  vision_aligning = false;
  Robot::m_limelight.ResetIntegral();
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  
  if (Robot::m_macro_superstructure.GetAuto() == false) {
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
    if (Robot::m_oi.GetDriverButton(vision_align_button) == true) {
      Robot::m_limelight.SetPipeline(2);
      if (Robot::m_limelight.GetTargetXTrans() == 0) {
        //goto manual_control;
        limelight_PID_value = Robot::m_limelight.GetPID(0, timer.Get());
        PID_value = Robot::m_drivetrain.GetGyroPID(Robot::m_drivetrain.GetAngle() - Robot::m_limelight.GetChassisAngle() + limelight_PID_value, timer.Get());
      } else {
        PID_value = 0;
        frc::SmartDashboard::PutNumber("Vision Driving PID", PID_value);
        frc::SmartDashboard::PutNumber("Vision PID", limelight_PID_value);
      }
      if (invert_driving == true) {
        Robot::m_drivetrain.SetSpeed(Robot::m_oi.GetAverageDriverInput() - PID_value, Robot::m_oi.GetAverageDriverInput() + PID_value);
      } else {
        Robot::m_drivetrain.SetSpeed(-Robot::m_oi.GetAverageDriverInput() - PID_value, -Robot::m_oi.GetAverageDriverInput() + PID_value);
      }
    } else {
      Robot::m_limelight.SetPipeline(0);
      manual_control:
        left_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_left_axis);
        right_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_right_axis);

        if (rumble_timer2.Get() < 0.35) {
          Robot::m_oi.SetDriverRumbleLeft(1);
          Robot::m_oi.SetDriverRumbleRight(1);
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

  x_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 180);
  y_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 180);

  frc::SmartDashboard::PutNumber("X Position", x_position);
  frc::SmartDashboard::PutNumber("Y Position", y_position);

  frc::SmartDashboard::PutNumber("Speed", (y_position - previous_y) / timer.Get());
  frc::SmartDashboard::PutNumber("Rotational Speed", (pi / 180) * (Robot::m_drivetrain.GetAngle() - previous_angle) / timer.Get());

  frc::SmartDashboard::PutNumber("NavX Value", Robot::m_drivetrain.GetAngle());
  frc::SmartDashboard::PutBoolean("Invert Driving", invert_driving);

  if (Robot::m_limelight.GetCamtranSize() == 12) {
    frc::SmartDashboard::PutNumber("Chassis X", Robot::m_limelight.GetChassisX());
    frc::SmartDashboard::PutNumber("Chassis Z", Robot::m_limelight.GetChassisZ());
    frc::SmartDashboard::PutNumber("Chassis Angle", Robot::m_limelight.GetChassisAngle());
  } else {
    frc::SmartDashboard::PutNumber("Randy X", -1410);
    frc::SmartDashboard::PutNumber("Randy Z", -1410);
    frc::SmartDashboard::PutNumber("Randy Angle", -1410);
  }
  frc::SmartDashboard::PutNumber("Camtran Size", Robot::m_limelight.GetCamtranSize());

  timer.Reset();
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_y = y_position;
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