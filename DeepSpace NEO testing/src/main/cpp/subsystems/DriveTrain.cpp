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
  return NavX->GetAngle();
}