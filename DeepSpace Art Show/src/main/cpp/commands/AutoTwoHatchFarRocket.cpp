/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoTwoHatchFarRocket.h"
#include "Robot.h"

AutoTwoHatchFarRocket::AutoTwoHatchFarRocket() {}

// Called just before this Command runs the first time
void AutoTwoHatchFarRocket::Initialize() {
  height = elevator_min_height;
  target_found = false;

  x_position = -47 * Robot::m_macro_superstructure.GetInvertedAuto();
  z_position = 67;

  stage = 0;

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
  path_timer = previous_timer;

  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();

  Robot::m_drivetrain.CalculatePath(-32 * Robot::m_macro_superstructure.GetInvertedAuto(), 116, -25 * Robot::m_macro_superstructure.GetInvertedAuto(), 150, 0);
}

// Called repeatedly when this Command is scheduled to run
void AutoTwoHatchFarRocket::Execute() {
  x_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * sin((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360);
  z_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * cos((Robot::m_drivetrain.GetAngle() + previous_angle) * pi / 360);

  switch (stage) {
    case 0:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-79 * Robot::m_macro_superstructure.GetInvertedAuto(), 183, -25 * Robot::m_macro_superstructure.GetInvertedAuto(), 150, 0) == true) {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        path_timer = previous_timer;
        Robot::m_drivetrain.CalculateRawPath(21.3508 * Robot::m_macro_superstructure.GetInvertedAuto(), 119.139, 53.75 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0);
        stage = 1;
      }
      break;
    case 1:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-110 * Robot::m_macro_superstructure.GetInvertedAuto(), 300, 28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        stage_distance = Robot::m_drivetrain.GetDistance();
        height = elevator_mid_hatch_height;
        stage = 2;
      }
      break;
    case 2:
      if (Robot::m_drivetrain.GetDistance() > stage_distance - 45) {
        /*if (Robot::m_limelight.GetTargetXTrans() 0 == 0) {
          if (target_found == false) {
            distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance - 47, m_timer.Get() - previous_timer);
            gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
          } else {
            latency_x = x_position - previous_x[sizeof(previous_times) / 8 - 1];
            latency_z = z_position - previous_z[sizeof(previous_times) / 8 - 1];
            latency_angle = Robot::m_drivetrain.GetAngle() - previous_angles[sizeof(previous_times) / 8 - 1];
          }
        } else {
          target_found = true;
          
          limelight_x = Robot::m_limelight.GetChassisX();
          limelight_z = Robot::m_limelight.GetChassisZ();
          limelight_angle = Robot::m_limelight.GetChassisAngle();

          if (Robot::m_limelight.GetCameraLatency() < m_timer.Get() - previous_timer) {
            latency_x = x_position * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[sizeof(previous_x) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
            latency_z = z_position * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[sizeof(previous_z) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
            latency_angle = Robot::m_drivetrain.GetAngle() * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
          } else {
            search = sizeof(previous_times) / 8 - 1;
            while (Robot::m_limelight.GetCameraLatency() + previous_times[search] > m_timer.Get()) {
              search--;
              if (search < 0) {
                distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance - 47, m_timer.Get() - previous_timer);
                gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
              }
            }

            latency_x = x_position - previous_x[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
            latency_z = z_position - previous_z[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
            latency_angle = Robot::m_drivetrain.GetAngle() - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - Robot::m_drivetrain.GetAngle() * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
          }
        }

        limelight_x += (sqrt(pow(latency_x, 2) + pow(latency_z, 2)) * sin(Robot::m_macro_superstructure.GetDirection(latency_x, latency_z) + limelight_angle - Robot::m_drivetrain.GetAngle()));
        limelight_z += (sqrt(pow(latency_x, 2) + pow(latency_z, 2)) * cos(Robot::m_macro_superstructure.GetDirection(latency_x, latency_z) + limelight_angle - Robot::m_drivetrain.GetAngle()));
        limelight_angle += latency_angle;

        limelight_PID_value = Robot::m_limelight.GetPID(limelight_x, m_timer.Get() - previous_timer);
        gyro_PID_value = Robot::m_drivetrain.GetGyroPID(Robot::m_drivetrain.GetAngle() - limelight_angle + limelight_PID_value, m_timer.Get() - previous_timer);
        distance_PID_value = Robot::m_drivetrain.GetDistancePID(Robot::m_drivetrain.GetDistance() - limelight_z, m_timer.Get() - previous_timer);
        Robot::m_drivetrain.CurvedAccelerate(distance_PID_value + gyro_PID_value, distance_PID_value - gyro_PID_value, m_timer.Get() - previous_timer);*/
      } else {
        Robot::m_drivetrain.SetSpeed(0, 0);
        Robot::m_hatch_stick.ExtendStick();
        height -= elevator_loading_station_displacement;
        stage = 3;
      }
      break;
    case 3:
      if (abs(Robot::m_elevator.GetHeight() - height) < elevator_deadband) {
        stage_distance = Robot::m_drivetrain.GetDistance();
        Robot::m_drivetrain.ResetDistanceIntegral();
        Robot::m_drivetrain.ResetGyroIntegral();
        stage = 4;
      }
      break;
    case 4:
      if (Robot::m_drivetrain.GetDistance() < stage_distance + 46) {
        distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance + 47, m_timer.Get() - previous_timer);
        gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
        Robot::m_drivetrain.CurvedAccelerate(distance_PID_value + gyro_PID_value, distance_PID_value - gyro_PID_value, m_timer.Get() - previous_timer);
      } else {
        Robot::m_drivetrain.ResetDistanceIntegral();
        Robot::m_drivetrain.ResetGyroIntegral();
        stage_distance = Robot::m_drivetrain.GetDistance();
        height = elevator_min_height;
        stage = 5;
      }
    case 5:
      if (Robot::m_drivetrain.GetAngle() * Robot::m_macro_superstructure.GetInvertedAuto() > drivetrain_gyro_deadband - 25) {
        gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
        distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance, m_timer.Get() - previous_timer);
        Robot::m_drivetrain.CurvedAccelerate(distance_PID_value + gyro_PID_value, distance_PID_value - gyro_PID_value, m_timer.Get() - previous_timer);
      } else {
        path_timer = previous_timer;
        Robot::m_drivetrain.CalculateRawPath(-57.1707 * Robot::m_macro_superstructure.GetInvertedAuto(), -134.434, 40 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0);
        stage = 6;
      }
      break;
    case 6:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-105 * Robot::m_macro_superstructure.GetInvertedAuto(), 154, 15 * Robot::m_macro_superstructure.GetInvertedAuto(), -200, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        path_timer = previous_timer;
        Robot::m_drivetrain.CalculateRawPath(7.44636 * Robot::m_macro_superstructure.GetInvertedAuto(), -139.838, -15 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0);
        stage = 7;
      }
      break;
    case 7:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-134 * Robot::m_macro_superstructure.GetInvertedAuto(), 17, 0, 0, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        height = elevator_low_hatch_height;
        stage = 8;
      }
      break;
    case 8:
      if (Robot::m_elevator.GetHeight() > elevator_low_hatch_height - elevator_deadband) {
        Robot::m_hatch_stick.RetractStick();
        Robot::m_drivetrain.CalculateRawPath(29 * Robot::m_macro_superstructure.GetInvertedAuto(), 137, 15 * Robot::m_macro_superstructure.GetInvertedAuto(), 200, 0);
        previous_timer = m_timer.Get();
        stage = 9;
      }
    case 9:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-105 * Robot::m_macro_superstructure.GetInvertedAuto(), 154, 15 * Robot::m_macro_superstructure.GetInvertedAuto(), 200, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        Robot::m_drivetrain.CalculateRawPath(-42.6172 * Robot::m_macro_superstructure.GetInvertedAuto(), 139.731, -40 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0);
        previous_timer = m_timer.Get();
        stage = 10;
      }
      break;
    case 10:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-110 * Robot::m_macro_superstructure.GetInvertedAuto(), 300, -25 * Robot::m_macro_superstructure.GetInvertedAuto(), 0, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        Robot::m_drivetrain.ResetDistanceIntegral();
        Robot::m_drivetrain.ResetGyroIntegral();
        stage_distance = Robot::m_drivetrain.GetDistance();
        stage = 11;
      }
      break;
    case 11:
      if (Robot::m_drivetrain.GetAngle() * Robot::m_macro_superstructure.GetInvertedAuto() > 28.75 - drivetrain_gyro_deadband) {
        gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
        distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance, m_timer.Get() - previous_timer);
        Robot::m_drivetrain.CurvedAccelerate(distance_PID_value + gyro_PID_value, distance_PID_value - gyro_PID_value, m_timer.Get() - previous_timer);
      } else {
        Robot::m_drivetrain.ResetDistanceIntegral();
        Robot::m_drivetrain.ResetGyroIntegral();
        Robot::m_limelight.ResetIntegral();
        stage_distance = Robot::m_drivetrain.GetDistance();
        stage = 12;
        target_found = false;
      }
      break;
    case 12:
      if (Robot::m_drivetrain.GetDistance() > stage_distance - 45) {
        /*if (Robot::m_limelight.GetTargetXTrans()0 == 0) {
          if (target_found == false) {
            distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance - 47, m_timer.Get() - previous_timer);
            gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
          } else {
            latency_x = x_position - previous_x[sizeof(previous_times) / 8 - 1];
            latency_z = z_position - previous_z[sizeof(previous_times) / 8 - 1];
            latency_angle = Robot::m_drivetrain.GetAngle() - previous_angles[sizeof(previous_times) / 8 - 1];
          }
        } else {
          target_found = true;
          
          limelight_x = Robot::m_limelight.GetChassisX();
          limelight_z = Robot::m_limelight.GetChassisZ();
          limelight_angle = Robot::m_limelight.GetChassisAngle();

          if (Robot::m_limelight.GetCameraLatency() < m_timer.Get() - previous_timer) {
            latency_x = x_position * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[sizeof(previous_x) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
            latency_z = z_position * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[sizeof(previous_z) / 8 - 1] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
            latency_angle = Robot::m_drivetrain.GetAngle() * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer));
          } else {
            search = sizeof(previous_times) / 8 - 1;
            while (Robot::m_limelight.GetCameraLatency() + previous_times[search] > m_timer.Get()) {
              search--;
              if (search < 0) {
                distance_PID_value = Robot::m_drivetrain.GetDistancePID(stage_distance - 47, m_timer.Get() - previous_timer);
                gyro_PID_value = Robot::m_drivetrain.GetGyroPID(28.75 * Robot::m_macro_superstructure.GetInvertedAuto(), m_timer.Get() - previous_timer);
              }
            }

            latency_x = x_position - previous_x[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_x[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
            latency_z = z_position - previous_z[search] * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - previous_z[search + 1] * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
            latency_angle = Robot::m_drivetrain.GetAngle() - previous_angle * (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)) - Robot::m_drivetrain.GetAngle() * (1 - (Robot::m_limelight.GetCameraLatency() / (m_timer.Get() - previous_timer)));
          }
        }

        limelight_x += (sqrt(pow(latency_x, 2) + pow(latency_z, 2)) * sin(Robot::m_macro_superstructure.GetDirection(latency_x, latency_z) + limelight_angle - Robot::m_drivetrain.GetAngle()));
        limelight_z += (sqrt(pow(latency_x, 2) + pow(latency_z, 2)) * cos(Robot::m_macro_superstructure.GetDirection(latency_x, latency_z) + limelight_angle - Robot::m_drivetrain.GetAngle()));
        limelight_angle += latency_angle;

        limelight_PID_value = Robot::m_limelight.GetPID(limelight_x, m_timer.Get() - previous_timer);
        gyro_PID_value = Robot::m_drivetrain.GetGyroPID(Robot::m_drivetrain.GetAngle() - limelight_angle + limelight_PID_value, m_timer.Get() - previous_timer);
        distance_PID_value = Robot::m_drivetrain.GetDistancePID(Robot::m_drivetrain.GetDistance() - limelight_z, m_timer.Get() - previous_timer);
        Robot::m_drivetrain.CurvedAccelerate(distance_PID_value + gyro_PID_value, distance_PID_value - gyro_PID_value, m_timer.Get() - previous_timer);*/
      } else {
        Robot::m_drivetrain.SetSpeed(0, 0);
        Robot::m_hatch_stick.ExtendStick();
        height -= elevator_loading_station_displacement;
        stage = 13;
      }
      break;
    case 13:
      if (Robot::m_elevator.GetHeight() < elevator_low_hatch_height + elevator_deadband - elevator_loading_station_displacement) {
        Robot::m_hatch_stick.RetractStick();
        height = elevator_min_height;
        stage = 14;
      }
      break;
    default:
      Robot::m_drivetrain.SetSpeed(0, 0);
  }
  
  Robot::m_elevator.Goto(height, m_timer.Get() - previous_timer);
  
  for (int count = 0; count < (sizeof(previous_times) / 8 - 1); count ++) {
    previous_x[count] = previous_x[count + 1];
    previous_z[count] = previous_z[count + 1];
    previous_times[count] = previous_times[count + 1];
    previous_angles[count] = previous_angles[count + 1];
  }
  
  previous_x[sizeof(previous_x) / 8 - 1] = x_position;
  previous_z[sizeof(previous_z) / 8 - 1] = z_position;
  previous_angles[sizeof(previous_angles) / 8 - 1] = Robot::m_drivetrain.GetAngle();
  previous_times[sizeof(previous_times) / 8 - 1] = m_timer.Get();
  
  previous_distance = Robot::m_drivetrain.GetDistance();
  previous_angle = Robot::m_drivetrain.GetAngle();
  previous_timer = m_timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTwoHatchFarRocket::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoTwoHatchFarRocket::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTwoHatchFarRocket::Interrupted() {}
