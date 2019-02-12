#include "subsystems/BallRoller.h"
#include "commands/BallRollerRun.h"
#include "Robot.h"

BallRoller::BallRoller() : Subsystem("BallRoller") {}

void BallRoller::InitDefaultCommand() {
  SetDefaultCommand(new BallRollerRun());
}

void BallRoller::RunIntake(double speed) {
  m_ball_roller.Set(-speed);
  frc::SmartDashboard::PutNumber("Ball Intake Speed", -speed);
}

void BallRoller::RollerDown() {
  ball_solenoid.Set(frc::DoubleSolenoid::kReverse);
  extended = true;
  frc::SmartDashboard::PutBoolean("Ball Intake State", true);
}

void BallRoller::RollerUp() {
  ball_solenoid.Set(frc::DoubleSolenoid::kForward);
  extended = false;
  frc::SmartDashboard::PutBoolean("Ball Intake State", false);
}

void BallRoller::RollerOff() {
  ball_solenoid.Set(frc::DoubleSolenoid::kOff);
  extended = false;
  frc::SmartDashboard::PutBoolean("Ball Intake State", false);
}

bool BallRoller::GetState() {
  return extended;
}