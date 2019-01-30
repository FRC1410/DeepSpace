#include "subsystems/Elevator.h"
#include "commands/ElevatorRun.h"

Elevator::Elevator() : Subsystem("ExampleSubsystem") {}

void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new ElevatorRun());
}

void Elevator::RunElevator(double speed) {
  m_elevator_left.Set(-speed);
  m_elevator_right.Set(speed);
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