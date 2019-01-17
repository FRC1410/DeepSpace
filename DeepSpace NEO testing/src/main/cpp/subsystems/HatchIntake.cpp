#include "subsystems/HatchIntake.h"
#include "commands/HatchWheelsRun.h"

HatchIntake::HatchIntake() : Subsystem("ExampleSubsystem") {}

void HatchIntake::InitDefaultCommand() {
  SetDefaultCommand(new HatchWheelsRun());
}

void HatchIntake::RunWheels(double speed) {
  m_left_wheel.Set(-speed);
  m_right_wheel.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
