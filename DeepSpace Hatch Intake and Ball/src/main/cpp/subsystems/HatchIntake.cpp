/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchIntake.h"

HatchIntake::HatchIntake() : Subsystem("ExampleSubsystem") {}

void HatchIntake::InitDefaultCommand() {
  SetDefaultCommand(new HatchWheelsRun());
}

void HatchIntake::RunWheels(double speed) {
  m_left_wheel.Set(-speed);
  m_right_wheel.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
