#include "subsystems/MacroSuperstructure.h"
#include "commands/MacroControl.h"

MacroSuperstructure::MacroSuperstructure() : Subsystem("ExampleSubsystem") {}

void MacroSuperstructure::InitDefaultCommand() {
  SetDefaultCommand(new MacroControl());
}

double MacroSuperstructure::CapValue(double value) {
  if (abs(value) < 1) {
    return value;
  } else {
    return abs(value)/value;
  }
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

void MacroSuperstructure::StartCompressor() {
  compressor.SetClosedLoopControl(true);
}

void MacroSuperstructure::StopCompressor() {
  compressor.SetClosedLoopControl(false);
}

double MacroSuperstructure::GetPressure() {
  return 50 * pressure_input.GetVoltage() - 25;
  frc::SmartDashboard::PutNumber("Pressure", 50 * pressure_input.GetVoltage() - 25);
}