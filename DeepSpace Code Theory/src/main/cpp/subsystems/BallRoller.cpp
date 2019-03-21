/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallRoller.h"
#include "commands/BallRollerRun.h"
#include "Robot.h"

BallRoller::BallRoller() : Subsystem("BallRoller") {}

void BallRoller::InitDefaultCommand() {
  SetDefaultCommand(new BallRollerRun());
}

void BallRoller::RunIntake(double speed) {
  m_ball_roller.Set(-speed);

  frc::Shuffleboard::GetTab("Debugging")
  .Add("Ball Roller", speed);
}

void BallRoller::RollerDown() {
  ball_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = true;
}

void BallRoller::RollerUp() {
  ball_solenoid.Set(frc::DoubleSolenoid::kForward);
  extended = false;
}

void BallRoller::RollerOff() {
  ball_solenoid.Set(frc::DoubleSolenoid::kOff);
  extended = false;
}

bool BallRoller::GetState() {
  return extended;
}