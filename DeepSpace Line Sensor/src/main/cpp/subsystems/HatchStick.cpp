#include "subsystems/HatchStick.h"
#include "commands/HatchStickActuate.h"

HatchStick::HatchStick() : Subsystem("ExampleSubsystem") {}

void HatchStick::InitDefaultCommand() {
  SetDefaultCommand(new HatchStickActuate());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
