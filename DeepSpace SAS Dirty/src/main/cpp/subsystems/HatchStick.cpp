/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchStick.h"
#include "commands/HatchStickActuate.h"
#include "Robot.h"

HatchStick::HatchStick() : Subsystem("HatchStick") {}

void HatchStick::InitDefaultCommand() {
  SetDefaultCommand(new HatchStickActuate());
}

void HatchStick::ExtendStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kForward);
  extended = true;
  //frc::SmartDashboard::PutBoolean("Hatch Stick State", true);
}

void HatchStick::RetractStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = false;
  //frc::SmartDashboard::PutBoolean("Hatch Stick State", false);
}

void HatchStick::StickOff() {
  stick_solenoid.Set(frc::DoubleSolenoid::kOff);
  extended = false;
  //frc::SmartDashboard::PutBoolean("Hatch Stick State", false);
}

bool HatchStick::GetState() {
  return extended;
}