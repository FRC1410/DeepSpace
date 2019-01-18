#include "subsystems/BallIntake.h"
#include "commands/Rumble.h"

BallIntake::BallIntake() : Subsystem("ExampleSubsystem") {}

void BallIntake::InitDefaultCommand() {
  SetDefaultCommand(new Rumble());
}

void BallIntake::RunIntake(double speed) {
  m_ball_intake.Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
