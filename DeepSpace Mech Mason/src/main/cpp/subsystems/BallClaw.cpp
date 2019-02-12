#include "subsystems/BallClaw.h"
#include "commands/BallClawWheelsRun.h"

BallClaw::BallClaw() : Subsystem("BallClaw") {}

void BallClaw::InitDefaultCommand() {
  SetDefaultCommand(new BallClawWheelsRun());
}

void BallClaw::RunWheels(double left, double right) {
  m_left_wheel.Set(left);
  m_right_wheel.Set(right);
  frc::SmartDashboard::PutNumber("Claw Left Speed", -left);
  frc::SmartDashboard::PutNumber("Claw Right Speed", right);
}

bool BallClaw::GetLimitSwitch() {
  return !(ball_limit_switch->Get());
}

