/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "commands/ElevatorRun.h"
#include "RobotMap.h"
#include "Robot.h"

Elevator::Elevator() : Subsystem("Elevator") {}

void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new ElevatorRun());
}

void Elevator::RunElevator(double speed, double PID) {
  current_vel = Robot::m_macro_superstructure.CapValue(speed);
  m_elevator_left.Set(-current_vel - PID);
  m_elevator_right.Set(current_vel + PID);
  //frc::SmartDashboard::PutNumber("Elevator Power", current_vel + PID);
}

void Elevator::Accelerate(double speed, double PID) {
  vel_difference = speed - current_vel;
  if (vel_difference > 0) {
    if (vel_difference < elevator_acceleration_rate) {
      RunElevator(speed, PID);
    } else {
      if (current_vel + elevator_acceleration_rate > elevator_weak_gravity && current_vel < elevator_strong_gravity) {
        if (current_vel > elevator_weak_gravity) {
          if (speed < elevator_strong_gravity + elevator_acceleration_rate) {
            RunElevator(speed, PID);
          } else {
            RunElevator(elevator_strong_gravity + elevator_acceleration_rate, PID);
          }
        } else {
          if (speed < elevator_strong_gravity) {
            RunElevator(speed, PID);
          } else {
            RunElevator(current_vel + elevator_acceleration_rate + elevator_strong_gravity - elevator_weak_gravity, PID);
          }
        }
      } else {
        RunElevator(current_vel + elevator_acceleration_rate, PID);
      }
    }
  } else {
    if (vel_difference > elevator_deceleration_rate) {
      RunElevator(speed, PID);
    } else {   
      if (current_vel + elevator_deceleration_rate < elevator_strong_gravity && current_vel > elevator_weak_gravity) {
        if (current_vel < elevator_strong_gravity) { 
          if (speed > elevator_weak_gravity + elevator_deceleration_rate) {
            RunElevator(speed, PID);
          } else {
            RunElevator(elevator_weak_gravity + elevator_deceleration_rate, PID);
          }
        } else {
          if (speed > elevator_weak_gravity) {
            RunElevator(speed, PID);
          } else {
            RunElevator(current_vel + elevator_deceleration_rate - elevator_strong_gravity + elevator_weak_gravity, PID);
          }
        }
      } else {
        RunElevator(current_vel + elevator_deceleration_rate, PID);
      }
    }
  }
}

void Elevator::Goto(double target_location, double previous_height, double time_difference) {
  if ((GetHeight() < lower_intake_intersect_height && target_location > lower_intake_intersect_height) || (target_location < upper_intake_intersect_height && GetHeight() > upper_intake_intersect_height)) {
    Robot::m_ball_roller.RollerDown();
  }
  if (abs(target_location - GetHeight()) < elevator_deadband && GetHeight() > elevator_min_height + elevator_bottom_buffer) {
    Accelerate(elevator_weak_gravity, 0);
  } else {
    if (target_location > GetHeight()) {
      if (target_location > elevator_min_height + elevator_bottom_buffer) {
        if (target_location - GetHeight() < 0.5 * (1 + elevator_deceleration_buffer) * abs(Robot::m_macro_superstructure.CapValue(current_vel + elevator_acceleration_rate) - elevator_strong_gravity) / (1 - elevator_strong_gravity) * (Robot::m_macro_superstructure.CapValue(current_vel + elevator_acceleration_rate) - elevator_strong_gravity) / (1 - elevator_strong_gravity) * elevator_deceleration_time * elevator_max_velocity) {
          if (target_location - GetHeight() < 0.5 * pow((current_vel - elevator_strong_gravity) / (1 - elevator_strong_gravity), 2) * elevator_deceleration_time * elevator_max_velocity) {
            Accelerate(elevator_weak_gravity, 0);
          } else {
            if (current_vel > elevator_strong_gravity) {
              PID_value = GetPID(previous_height + ((current_vel - elevator_strong_gravity) / (1 - elevator_strong_gravity)) * elevator_max_velocity * time_difference, time_difference);
            } else if (current_vel < elevator_weak_gravity) {
              PID_value = GetPID(previous_height + ((current_vel - elevator_weak_gravity) / (1 - elevator_strong_gravity)) * elevator_max_velocity * time_difference, time_difference);
            } else {
              PID_value = GetPID(previous_height, time_difference);
            }
            RunElevator(sqrt(2 * (target_location - GetHeight()) / (elevator_deceleration_time * elevator_max_velocity)) + elevator_strong_gravity, PID_value);
          }
        } else {
          Accelerate(1, 0);
        }
      } else {
        Accelerate(0, 0);
      }
    } else {
      if (target_location > elevator_min_height + elevator_bottom_buffer || GetHeight() > elevator_min_height + elevator_bottom_buffer) {
        if (GetHeight() - target_location < 0.5 * (1 + elevator_acceleration_buffer) * abs((elevator_weak_gravity - Robot::m_macro_superstructure.CapValue(current_vel + elevator_acceleration_rate)) / (1 + elevator_weak_gravity)) * ((elevator_weak_gravity - Robot::m_macro_superstructure.CapValue(current_vel + elevator_acceleration_rate)) / (1 + elevator_weak_gravity)) * elevator_acceleration_time * elevator_max_velocity) {
          if (GetHeight() - target_location < 0.5 * abs((elevator_weak_gravity - current_vel) / (1 + elevator_weak_gravity)) * ((elevator_weak_gravity - current_vel) / (1 + elevator_weak_gravity)) * elevator_acceleration_time * elevator_max_velocity) {
            Accelerate(elevator_weak_gravity, 0);
          } else {
            if (current_vel > elevator_strong_gravity) {
              PID_value = GetPID(previous_height + ((current_vel - elevator_strong_gravity) / (1 - elevator_strong_gravity)) * elevator_max_velocity * time_difference, time_difference);
            } else if (current_vel < elevator_weak_gravity) {
              PID_value = GetPID(previous_height + ((current_vel - elevator_weak_gravity) / (1 - elevator_strong_gravity)) * elevator_max_velocity * time_difference, time_difference);
            } else {
              PID_value = GetPID(previous_height, time_difference);
            }
            RunElevator(-sqrt(2 * (GetHeight() - target_location) / (elevator_acceleration_time * elevator_max_velocity * ((1 + elevator_weak_gravity) / (1 - elevator_strong_gravity)))) + elevator_weak_gravity, PID_value);
          }
        } else {
          Accelerate(-1, 0);
        }
      } else {
        Accelerate(0, 0);
      }
    }
  }
}

double Elevator::GetInput() {
  return current_vel;
}

double Elevator::GetLeftRevolutions() {
  return -(m_left_encoder.GetPosition() - initial_left_revolutions);
}

double Elevator::GetRightRevolutions() {
  return m_right_encoder.GetPosition() - initial_right_revolutions;
}

double Elevator::GetAverageRevolutions() {
  if (m_left_encoder.GetPosition() == 0) {
    return GetRightRevolutions();
  } else if (m_right_encoder.GetPosition() == 0) {
    return GetLeftRevolutions();
  } else {
    return (GetLeftRevolutions() + GetRightRevolutions()) / 2;
  }
}

void Elevator::ResetEncoders() {
  initial_left_revolutions = m_left_encoder.GetPosition();
  initial_right_revolutions = m_right_encoder.GetPosition();
}

double Elevator::GetHeight() {
  return (GetAverageRevolutions() / elevator_calibration_revolutions) * (elevator_calibration_height - elevator_min_height) + elevator_min_height;
}

double Elevator::GetPID(double target, double time_difference) {
  error = target - GetHeight();
  frc::SmartDashboard::PutNumber("Elevator PID Error", error);
  P = elevator_kP * error;
  I += elevator_kI * error * time_difference;
  D = elevator_kD * (error - previous_error) * time_difference;
  previous_error = error;
  return P + I + D;
}

void Elevator::ResetIntegral() {
  I = 0;
  previous_error = 0;
}

double Elevator::GetLeftTemperature() {
  return m_elevator_left.GetMotorTemperature();
}

double Elevator::GetRightTemperature() {
  return m_elevator_right.GetMotorTemperature();
}