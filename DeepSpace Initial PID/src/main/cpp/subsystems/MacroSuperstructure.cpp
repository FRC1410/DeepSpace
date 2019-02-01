#include "subsystems/MacroSuperstructure.h"
#include "commands/MacroControl.h"

MacroSuperstructure::MacroSuperstructure() : Subsystem("ExampleSubsystem") {}

void MacroSuperstructure::InitDefaultCommand() {
  SetDefaultCommand(new MacroControl());
}

void MacroSuperstructure::SetProfile(int direction) {
  switch (direction) {
    case hatch_profile_direction:
      profile = hatch_profile_number;
      break;
    case ball_profile_direction:
      profile = ball_profile_number;
      break;
    case climber_profile_direction:
      profile = climber_profile_number;
      break;
    case reset_mechanisms_direction:
      reset = true;
      break;
    default:
      reset = false;
  }
}

bool MacroSuperstructure::GetReset() {
  return reset;
}

int MacroSuperstructure::GetProfile() {
  return profile;
}

void MacroSuperstructure::RunLEDs(double value) {
  LEDs.Set(value);  
}

void MacroSuperstructure::SetAuto(bool auto_data) {
  running_auto = auto_data;
}

bool MacroSuperstructure::GetAuto() {
  return running_auto;
}

/*void MacroSuperstructure::StartCompressor() {
  compress->SetClosedLoopControl(true);
}

void MacroSuperstructure::StopCompressor() {
  compress->SetClosedLoopControl(false);
}*/