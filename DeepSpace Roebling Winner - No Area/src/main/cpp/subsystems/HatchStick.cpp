/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HatchStickActuate.h"
#include "Robot.h"

HatchStick::HatchStick() : Subsystem("HatchStick") {}

void HatchStick::InitDefaultCommand() {
  SetDefaultCommand(new HatchStickActuate());
}

void HatchStick::RunWheels(double speed) {
  speed = Robot::m_macro_superstructure.CapValue(speed, hatch_stick_limiter);
  //m_wheels.Set(speed);
  shuffleboard_flex_power.SetDouble(speed);
}

void HatchStick::ExtendStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kForward);
  extended = true;
  shuffleboard_stick.SetBoolean(extended);
}

void HatchStick::RetractStick() {
  stick_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = false;
  shuffleboard_stick.SetBoolean(extended);
}

bool HatchStick::GetState() {
  return extended;
}