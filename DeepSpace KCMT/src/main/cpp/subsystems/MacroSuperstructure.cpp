/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/MacroSuperstructure.h"
#include "commands/MacroControl.h"
#include "Robot.h"

MacroSuperstructure::MacroSuperstructure() : Subsystem("ExampleSubsystem") {
  m_chooser.SetDefaultOption("Blue", "blue");
  m_chooser.AddOption("Red", "red");

  frc::Shuffleboard::GetTab("Drivers").Add("Alliance?", m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser).WithPosition(8, 0).WithSize(1, 1);
}

void MacroSuperstructure::InitDefaultCommand() {
  SetDefaultCommand(new MacroControl());
}

void MacroSuperstructure::SetFMSAuto(bool auto_data) {
  FMS_auto = auto_data;
}

bool MacroSuperstructure::GetFMSAuto() {
  return FMS_auto;
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

void MacroSuperstructure::SetProfile(int direction) {
  if (direction == reset_mechanisms_direction) {
    reset = true;
  } else {
    reset = false;
    if (direction == hatch_profile_direction) {
      frc::SmartDashboard::PutBoolean("Hatch", true);
      frc::SmartDashboard::PutBoolean("Cargo", false);

      shuffleboard_hatch.SetBoolean(true);
      shuffleboard_cargo.SetBoolean(false);
      shuffleboard_defense.SetBoolean(false);

      profile = hatch_profile_number;
    } else if (direction == ball_profile_direction) {
      frc::SmartDashboard::PutBoolean("Hatch", false);
      frc::SmartDashboard::PutBoolean("Cargo", true);

      shuffleboard_hatch.SetBoolean(false);
      shuffleboard_cargo.SetBoolean(true);
      shuffleboard_defense.SetBoolean(false);
      
      profile = ball_profile_number;
    } else if (direction == defense_direction) {
      Robot::m_ball_roller.RollerUp();
      Robot::m_hatch_stick.RetractStick();
      profile = defense_profile_number;

      frc::SmartDashboard::PutBoolean("Hatch", false);
      frc::SmartDashboard::PutBoolean("Cargo", false);

      shuffleboard_hatch.SetBoolean(false);
      shuffleboard_cargo.SetBoolean(false);
      shuffleboard_defense.SetBoolean(true);

      SetLEDs(lime_preset);
    }
  }
}

int MacroSuperstructure::GetProfile() {
  return profile;
}

bool MacroSuperstructure::GetReset() {
  return reset;
}

void MacroSuperstructure::SetCompressor(bool state) {
  shuffleboard_compressor.SetBoolean(state);
  m_compressor.SetClosedLoopControl(state);
}

double MacroSuperstructure::GetPressure() {
  frc::SmartDashboard::PutNumber("Pressure", 50 * pressure_input.GetVoltage() - 25);
  shuffleboard_pressure.SetDouble(50 * pressure_input.GetVoltage() - 25);
  return 50 * pressure_input.GetVoltage() - 25;
}

double MacroSuperstructure::GetBatteryVoltage() {
  frc::SmartDashboard::PutNumber("Voltage", frc::DriverStation::GetInstance().GetBatteryVoltage());
  shuffleboard_voltage.SetDouble(frc::DriverStation::GetInstance().GetBatteryVoltage());
  return frc::DriverStation::GetInstance().GetBatteryVoltage();
}

void MacroSuperstructure::SetLEDs(double value) {
  shuffleboard_LEDs.SetDouble(value);
  LEDs.Set(value);
}

void MacroSuperstructure::SetWarnings(bool warning, double time) {
  frc::SmartDashboard::PutBoolean("Warnings", warning);
  frc::SmartDashboard::PutNumber("Time", time);

  shuffleboard_warnings.SetBoolean(warning);
  shuffleboard_time.SetDouble(time);
}

bool MacroSuperstructure::GetAlliance() {
  if (m_chooser.GetSelected() == "blue") {
    alliance_bool = 0;
  } else if (m_chooser.GetSelected() == "red") {
    alliance_bool = 1;
  }

  return alliance_bool;
}

void MacroSuperstructure::SetStage(double stage) {
  shuffleboard_stage.SetDouble(stage);
}

double MacroSuperstructure::CapValue(double value, double cap) {
  if (abs(value) > cap) {
    return (abs(value) / value) * cap;
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
    return pi / 2 - abs(y) / y;
  }
}