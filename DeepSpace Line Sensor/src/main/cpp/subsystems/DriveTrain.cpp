#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new Drive());
}

void DriveTrain::TankDrive(double left, double right) {
  m_front.TankDrive(left, right);
  m_back.TankDrive(left, right);
}

void DriveTrain::ResetNavX() {
  NavX->Reset();
}

double DriveTrain::GetAngle() {
  return NavX->GetRoll();
}

bool DriveTrain::GetLeftSensor() {
  return left_tape_sensor->Get();;
}

bool DriveTrain::GetMiddleSensor() {
  return middle_tape_sensor->Get();;
}

bool DriveTrain::GetRightSensor() {
  return right_tape_sensor->Get();;
}