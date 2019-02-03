#include "subsystems/BallRoller.h"
#include "commands/BallRollerRun.h"

BallRoller::BallRoller() : Subsystem("ExampleSubsystem") {}

void BallRoller::InitDefaultCommand() {
  SetDefaultCommand(new BallRollerRun());
}

void BallRoller::RunIntake(double speed) {
  m_ball_roller.Set(-speed);
}

void BallRoller::RollerDown() {
  ball_solenoid.Set(frc::DoubleSolenoid::kForward);
}

void BallRoller::RollerUp() {
  ball_solenoid.Set(frc::DoubleSolenoid::kReverse);
}

void BallRoller::RollerOff() {
  ball_solenoid.Set(frc::DoubleSolenoid::kOff);
}