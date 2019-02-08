#include "subsystems/BallClaw.h"
#include "commands/BallClawWheelsRun.h"

BallClaw::BallClaw() : Subsystem("BallClaw") {}

void BallClaw::InitDefaultCommand() {
  SetDefaultCommand(new BallClawWheelsRun());
}

void BallClaw::RunWheels(double speed) {
  m_left_wheel.Set(-speed);
  m_right_wheel.Set(speed);
  left_speed = -speed;
  right_speed = speed;
  frc::SmartDashboard::PutNumber("Claw Left Speed", -speed);
  frc::SmartDashboard::PutNumber("Claw Right Speed",speed);
}

void BallClaw::RunLeftWheels(double speed){
  m_left_wheel.Set(-speed);
  left_speed = -speed;
  frc::SmartDashboard::PutNumber("Claw Left Speed", -speed);

}

void BallClaw::RunRightWheels(double speed) {
  m_right_wheel.Set(speed);
  right_speed = speed;
  frc::SmartDashboard::PutNumber("Claw Right Speed", speed);
}

void BallClaw::RunWheelsIndividual(double left, double right) {
  RunLeftWheels(left);    //Wow such code
  RunRightWheels(right);
}

bool BallClaw::GetLimitSwitch() {
  return !(ball_limit_switch->Get());
}

