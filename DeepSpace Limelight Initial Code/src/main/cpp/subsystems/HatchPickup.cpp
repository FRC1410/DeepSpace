#include "subsystems/HatchPickup.h"
#include "subsystems/HatchPickup.h"
#include "commands/HatchPickupRotate.h"

HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem") {}

void HatchPickup::InitDefaultCommand() {
  SetDefaultCommand(new HatchPickupRotate());
}

void HatchPickup::RotatePickup(double speed) {
  m_rotator.Set(0.7 * speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
