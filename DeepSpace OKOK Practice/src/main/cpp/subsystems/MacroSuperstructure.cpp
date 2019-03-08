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

void MacroSuperstructure::SetAuto(bool auto_data) {
  running_auto = auto_data;
}

bool MacroSuperstructure::GetAuto() {
  return running_auto;
}

void MacroSuperstructure::SetInvertedAuto(bool input) {
  if (input == true) {
    inverted_auto = -1;
  } else {
    inverted_auto = 1;
  }
}

int MacroSuperstructure::GetInvertedAuto() {
  return inverted_auto;
}

void MacroSuperstructure::SetHandoffStage(int stage) {
  handoff_stage = stage;
}

int MacroSuperstructure::GetHandoffStage() {
  return handoff_stage;
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
      SetHandoffStage(0);
      break;
    default:
      reset = false;
  }
}

int MacroSuperstructure::GetProfile() {
  return profile;
}

bool MacroSuperstructure::GetReset() {
  return reset;
}

void MacroSuperstructure::SetCompressor(bool state) {
  m_compressor.SetClosedLoopControl(state);
}

double MacroSuperstructure::GetPressure() {
  return 50 * pressure_input.GetVoltage() - 25;
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

double MacroSuperstructure::CapValue(double value) {
  if (abs(value) > 1) {
    return abs(value)/value;
  } else {
    return value;
  }
}

double MacroSuperstructure::GetDirection(double x, double y) {
  if (x > 0) {
    return pi / 2 - atan(y / x);
  } else if (x < 0) {
    return 3 * pi / 2 - atan(y / x);
  } else {
    return pi / 2 * (1 - abs(y) / y);
  }
}