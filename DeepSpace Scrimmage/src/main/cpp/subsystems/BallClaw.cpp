/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/BallClaw.h"
#include "commands/BallClawWheelsRun.h"

BallClaw::BallClaw() : Subsystem("BallClaw") {}

void BallClaw::InitDefaultCommand() {
  SetDefaultCommand(new BallClawWheelsRun());
}

void BallClaw::DisableSafety() {
  m_left_wheel.SetSafetyEnabled(false);
  m_right_wheel.SetSafetyEnabled(false);
}

void BallClaw::RunWheels(double left, double right) {
  m_left_wheel.Set(-left);
  m_right_wheel.Set(right);
  //frc::SmartDashboard::PutNumber("Claw Left Speed", -left);
  //frc::SmartDashboard::PutNumber("Claw Right Speed", right);
}

bool BallClaw::GetLimitSwitch() {
  return !(ball_limit_switch->Get());
}

