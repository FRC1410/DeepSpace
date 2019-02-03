#include "subsystems/Elevator.h"
#include "commands/ElevatorRun.h"
#include "RobotMap.h"

Elevator::Elevator() : Subsystem("ExampleSubsystem") {}

void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new ElevatorRun());
}

void Elevator::RunElevator(double speed) {
  if (abs(speed) < 1) {
    m_elevator_left.Set(-speed);
    m_elevator_right.Set(speed);
  } else {
    m_elevator_left.Set(-abs(speed)/speed);
    m_elevator_right.Set(abs(speed)/speed);
  }
}

void Elevator::Accelerate(double speed) {
  vel_difference = speed - current_vel;
  if(abs(vel_difference) <= 1 / (50 * elevator_accleration_time)) {
    RunElevator(speed);
  } else {
    if(vel_difference > 0) {
      RunElevator(speed + (1 / (50 * elevator_accleration_time)));
    } else {
      RunElevator(speed - (1 / (50 * elevator_accleration_time)));
    }
  }
}

double Elevator::GetLeftRevolutions() {
  return -m_left_encoder.GetPosition();
}

double Elevator::GetRightRevolutions() {
  return m_right_encoder.GetPosition();
}

double Elevator::GetAverageRevolutions() {
  if (GetLeftRevolutions() == 0) {
    return GetLeftRevolutions();
  } else if (GetRightRevolutions() == 0) {
    return GetRightRevolutions();
  } else {
    return (GetLeftRevolutions() + GetRightRevolutions()) / 2;
  }
}

double Elevator::GetLeftTemperature() {
  return m_elevator_left.GetMotorTemperature();
}

double Elevator::GetRightTemperature() {
  return m_elevator_right.GetMotorTemperature();
}

double Elevator::GetHeight() {
  return (GetAverageRevolutions() / elevator_max_revolutions) * (elevator_max_height - elevator_min_height) - initial_height + elevator_min_height;
}

void Elevator::ResetHeight() {
  initial_height = (GetAverageRevolutions() / elevator_max_revolutions) * (elevator_max_height - elevator_min_height);
}

double Elevator::GetPID(double previous_error, double target, double time_difference) {
  error = target - Elevator::GetHeight();
  P = elevator_kP * error;
  I += elevator_kI * error * time_difference;   //could be wrong syntax :(
  D = elevator_kD * (error - previous_error) * time_difference;
  previous_error = error;
  return P + I + D;
}

void Elevator::ResetIntegral() {
  I = 0;
}