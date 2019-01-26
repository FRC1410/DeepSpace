#include "subsystems/BallClaw.h"
#include "commands/BallClawWheelsRun.h"

BallClaw::BallClaw() : Subsystem("ExampleSubsystem") {}

void BallClaw::InitDefaultCommand() {
  SetDefaultCommand(new BallClawWheelsRun());
}

void BallClaw::RunWheels(double speed) {
  m_left_wheel.Set(-speed);
  m_right_wheel.Set(speed);
}
 
 bool BallClaw::GetLimitSwitch() {
  return ball_limit_switch->Get();
 }