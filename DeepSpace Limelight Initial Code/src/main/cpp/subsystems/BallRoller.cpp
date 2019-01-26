#include "subsystems/BallRoller.h"
#include "commands/BallRollerRun.h"

BallRoller::BallRoller() : Subsystem("ExampleSubsystem") {}

void BallRoller::InitDefaultCommand() {
  SetDefaultCommand(new BallRollerRun());
}

void BallRoller::RunIntake(double speed) {
  m_ball_roller.Set(-0.7 * speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
