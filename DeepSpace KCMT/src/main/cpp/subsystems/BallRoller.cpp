/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallRoller.h"
#include "commands/BallRollerRun.h"

BallRoller::BallRoller() : Subsystem("BallRoller") {}

void BallRoller::InitDefaultCommand() {
  SetDefaultCommand(new BallRollerRun());
}

void BallRoller::RunIntake(double speed) {
  m_ball_roller.Set(-speed);
  shuffleboard_power.SetDouble(speed);
}

void BallRoller::RollerDown() {
  ball_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = true;
  shuffleboard_roller.SetBoolean(extended);
}

void BallRoller::RollerUp() {
  ball_solenoid.Set(frc::DoubleSolenoid::kForward);
  extended = false;
  shuffleboard_roller.SetBoolean(extended);
}

bool BallRoller::GetState() {
  return extended;
}