/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallIntake.h"

BallIntake::BallIntake() : Subsystem("ExampleSubsystem") {}

void BallIntake::InitDefaultCommand() {
  SetDefaultCommand(new BallIntakeRun());
}

void BallIntake::RunIntake(double speed) {
  m_ball_intake.Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
