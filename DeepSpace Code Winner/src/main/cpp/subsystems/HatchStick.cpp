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
}

void HatchStick::RetractStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = false;
}

void HatchStick::StickOff() {
  stick_solenoid.Set(frc::DoubleSolenoid::kOff);
  extended = false;
}

bool HatchStick::GetState() {
  return extended;
}