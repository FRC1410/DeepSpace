/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018-2019 FIRST. All Rights Reserved.                        */
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

void Elevator::RunElevator(double speed) {
  if (GetHeight() > elevator_max_height && speed > 0) {
    current_velocity = 0;
  } else {
    current_velocity = Robot::m_macro_superstructure.CapValue(speed);
  }
  //m_elevator_left.Set(-current_velocity);
  //m_elevator_right.Set(current_velocity);
  
  frc::Shuffleboard::GetTab("Debugging")
  .Add("Elevator", current_velocity);
}

void Elevator::Accelerate(double speed, double time_difference) {
  if (abs(speed - current_velocity) < time_difference / elevator_acceleration_time) {
    RunElevator(speed);
  } else {
    RunElevator(current_velocity + (abs(speed - current_velocity) / (speed - current_velocity)) * time_difference / elevator_acceleration_time);
  }
}

void Elevator::Goto(double target_location, double time_difference) {
  if ((GetHeight() < lower_intake_intersect_height && target_location > lower_intake_intersect_height) || (target_location < upper_intake_intersect_height && GetHeight() > upper_intake_intersect_height)) {
    Robot::m_ball_roller.RollerDown();
  }
  if (abs(target_location - GetHeight()) < elevator_deadband && GetHeight() > elevator_min_height + elevator_bottom_buffer) {
    Accelerate(elevator_gravity, time_difference);
  } else {
    if (target_location < elevator_min_height + elevator_bottom_buffer && GetHeight() < elevator_min_height + elevator_bottom_buffer) {
      Accelerate(0, time_difference);
    } else {
      Accelerate(GetPID(target_location, time_difference) + elevator_gravity, time_difference);
    }
  }
}

double Elevator::GetInput() {
  return current_velocity;
}

void Elevator::ResetEncoders() {
  initial_left_revolutions = m_left_encoder.GetPosition();
  initial_right_revolutions = m_right_encoder.GetPosition();
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

double Elevator::GetHeight() {
  return (GetAverageRevolutions() / elevator_calibration_revolutions) * (elevator_calibration_height - elevator_min_height) + elevator_min_height;
}

double Elevator::GetPID(double target, double time_difference) {
  error = target - GetHeight();
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