#include "subsystems/HatchStick.h"
#include "commands/HatchStickActuate.h"

HatchStick::HatchStick() : Subsystem("ExampleSubsystem") {}

void HatchStick::InitDefaultCommand() {
  SetDefaultCommand(new HatchStickActuate());
}

void HatchStick::ExtendStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kForward);
}

void HatchStick::RetractStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kReverse);
}

void HatchStick::StickOff() {
  stick_solenoid.Set(frc::DoubleSolenoid::kOff);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
