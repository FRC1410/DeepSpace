#include "subsystems/BallClaw.h"

BallClaw::BallClaw() : Subsystem("ExampleSubsystem") {}

void BallClaw::InitDefaultCommand() {
  SetDefaultCommand(new BallClawWheelsRun());
}

void BallClaw::RunWheels(double speed) {
  m_left_wheel.Set(-speed);
  m_right_wheel.Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.