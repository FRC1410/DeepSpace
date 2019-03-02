/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/MacroSuperstructure.h"
#include "commands/MacroControl.h"

MacroSuperstructure::MacroSuperstructure() : Subsystem("ExampleSubsystem") {}

void MacroSuperstructure::InitDefaultCommand() {
  SetDefaultCommand(new MacroControl());
}

double MacroSuperstructure::CapValue(double value) {
  if (value == 0) {
    return 0;
  } else if (abs(value) < 1) {
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
      SetHandoffState(0);
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

void MacroSuperstructure::SetLeftLEDs(double value) {
  left_LEDs.Set(value);  
}

void MacroSuperstructure::SetRightLEDs(double value) {
  right_LEDs.Set(value);  
}

void MacroSuperstructure::SetLEDs(double value) {
  left_LEDs.Set(value);
  right_LEDs.Set(value);
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

int MacroSuperstructure::SetHandoffState(int state) {
  handoff_state = state;
}

int MacroSuperstructure::GetHandoffState() {
  return handoff_state;
}