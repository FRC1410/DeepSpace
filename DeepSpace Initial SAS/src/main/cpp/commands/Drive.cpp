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
  invert_driving = true;
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();

  m_timer.Reset();
  m_timer.Start();

  invert_timer = 0;
  previous_timer = -0.02;

  for (int count = 0; count < sizeof(previous_times) / 8; count++) {
    previous_x[count] = Robot::m_drivetrain.GetX();
    previous_z[count] = Robot::m_drivetrain.GetZ();
    previous_angles[count] = Robot::m_drivetrain.GetAngle();
    previous_times[count] = (double(count) / 50) - double(sizeof(previous_times) / 8) / 50;
  }
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  Robot::m_drivetrain.IncrementX((Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));
  Robot::m_drivetrain.IncrementZ((Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360));

  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
      if (invert_button_was_pressed == false) {
        invert_timer = m_timer.Get();
        invert_driving = !invert_driving;
      }
      invert_button_was_pressed = true;
    } else {
      invert_button_was_pressed = false;
    }

    if (Robot::m_oi.GetDriverButton(vision_align_button) == true) {
      if (vision_button_was_pressed == false) {
        Robot::m_limelight.ResetIntegral();
        Robot::m_limelight.SetPipeline(2);
      }

      if (Robot::m_limelight.GetTargetXTrans() == 0) {
        if (target_found == false) {
          goto manual_control;
        } else {
          latency_x = Robot::m_drivetrain.GetX() - previous_x[sizeof(previous_times) / 8 - 1];
          latency_z = Robot::m_drivetrain.GetZ() - previous_z[sizeof(previous_times) / 8 - 1];
          latency_angle = Robot::m_drivetrain.GetAngle() - previous_angles[sizeof(previous_times) / 8 - 1];
        }
      } else {
        target_found = true;
        
        limelight_x = Robot::m_limelight.GetChassisX();
        limelight_angle = Robot::m_limelight.GetChassisAngle();

        if (Robot::m_limelight.GetCameraLatency() < m_timer.Get() - previous_timer) {
          latency_x = Robot::m_drivetrain.GetX() * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[sizeof(previous_x) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
          latency_z = Robot::m_drivetrain.GetZ() * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[sizeof(previous_z) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
          latency_angle = Robot::m_drivetrain.GetAngle() * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
        } else {
          search = sizeof(previous_times) / 8 - 1;
          while (Robot::m_limelight.GetCameraLatency() + previous_times[search] > m_timer.Get()) {
            search--;
            if (search < 0) {
              goto manual_control;
            }
          }

          latency_x = Robot::m_drivetrain.GetX() - previous_x[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
          latency_z = Robot::m_drivetrain.GetZ() - previous_z[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
          latency_angle = Robot::m_drivetrain.GetAngle() - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - Robot::m_drivetrain.GetAngle() * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
        }
      }

      limelight_x += (sqrt(pow(latency_x, 2) + pow(latency_z, 2)) * sin(Robot::m_macro_superstructure.GetDirection(latency_x, latency_z) + limelight_angle - Robot::m_drivetrain.GetAngle()));
      limelight_angle += latency_angle;

      limelight_PID_value = Robot::m_limelight.GetPID(limelight_x, m_timer.Get() - previous_timer);
      PID_value = Robot::m_drivetrain.GetGyroPID(Robot::m_drivetrain.GetAngle() - limelight_angle + limelight_PID_value, m_timer.Get() - previous_timer);

      if (invert_driving == true) {
        Robot::m_drivetrain.CurvedAccelerate(Robot::m_oi.GetAverageDriverInput() + PID_value, Robot::m_oi.GetAverageDriverInput() - PID_value, m_timer.Get() - previous_timer);
      } else {
        Robot::m_drivetrain.CurvedAccelerate(-Robot::m_oi.GetAverageDriverInput() + PID_value, -Robot::m_oi.GetAverageDriverInput() - PID_value, m_timer.Get() - previous_timer);
      }
      vision_button_was_pressed = true;
    } else {
      target_found = false;
      vision_button_was_pressed = false;
      Robot::m_limelight.SetPipeline(0);

      manual_control:
        left_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_left_axis);
        right_stick_amount = -Robot::m_oi.GetDriverAxis(drivetrain_right_axis);

        if (invert_driving == false) {
          if ((m_timer.Get() - invert_timer) < single_rumble_time) {
            Robot::m_oi.SetDriverRumbleLeft(1);
            Robot::m_oi.SetDriverRumbleRight(1);
          } else {
            Robot::m_oi.SetDriverRumbleLeft(0);
            Robot::m_oi.SetDriverRumbleRight(0);
          }
        } else {
          if ((m_timer.Get() - invert_timer) < double_rumble_time || ((m_timer.Get() - invert_timer) > (2 * double_rumble_time) && (m_timer.Get() - invert_timer) < (3 * double_rumble_time))) {
            Robot::m_oi.SetDriverRumbleLeft(1);
            Robot::m_oi.SetDriverRumbleRight(1);
          } else {
            Robot::m_oi.SetDriverRumbleLeft(0);
            Robot::m_oi.SetDriverRumbleRight(0);
          }
        }

        if (invert_driving == false) {
          Robot::m_drivetrain.SetCurvedSpeed(left_stick_amount, right_stick_amount);    
        } else {
          Robot::m_drivetrain.SetCurvedSpeed(-right_stick_amount, -left_stick_amount);
        }
    }
  }

  for (int count = 0; count < (sizeof(previous_times) / 8 - 1); count ++) {
    previous_x[count] = previous_x[count + 1];
    previous_z[count] = previous_z[count + 1];
    previous_times[count] = previous_times[count + 1];
    previous_angles[count] = previous_angles[count + 1];
  }

  previous_x[sizeof(previous_x) - 1] = Robot::m_drivetrain.GetX();
  previous_z[sizeof(previous_z) - 1] = Robot::m_drivetrain.GetZ();
  previous_angles[sizeof(previous_angles) - 1] = Robot::m_drivetrain.GetAngle();
  previous_times[sizeof(previous_times) - 1] = m_timer.Get();

  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_timer = m_timer.Get();
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