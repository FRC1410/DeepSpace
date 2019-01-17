#include "subsystems/BallIntake.h"
#include "commands/BallIntakeRun.h"

BallIntake::BallIntake() : Subsystem("ExampleSubsystem") {}

void BallIntake::InitDefaultCommand() {
  SetDefaultCommand(new BallIntakeRun());
}

void BallIntake::RunIntake(double speed) {
  m_ball_intake.Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
