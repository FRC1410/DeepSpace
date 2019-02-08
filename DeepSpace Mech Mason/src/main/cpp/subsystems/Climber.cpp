#include "subsystems/Climber.h"
#include "commands/ClimberExtend.h"
#include "Robot.h"

Climber::Climber() : Subsystem("Climber") {}

void Climber::InitDefaultCommand() {
  SetDefaultCommand(new ClimberExtend());
}

void Climber::ExtendFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kForward);
  front_extended = true;
  frc::SmartDashboard::PutBoolean("Climber Front State", true);
}

void Climber::ExtendBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kReverse);
  back_extended = true;
  frc::SmartDashboard::PutBoolean("Climber Back State", true);
}

void Climber::RetractFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kReverse);
  front_extended = false;
  frc::SmartDashboard::PutBoolean("Climber Front State", false);
}

void Climber::RetractBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kForward);
  back_extended = false;
  frc::SmartDashboard::PutBoolean("Climber Back State", false);
}

void Climber::FrontOff(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kOff);
  front_extended = false;
  frc::SmartDashboard::PutBoolean("Climber Front State", false);
}

void Climber::BackOff(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kOff);
  back_extended = false;
  frc::SmartDashboard::PutBoolean("Climber Back State", false);
}

bool Climber::ReturnFrontState() {
  return front_extended;
}

bool Climber::ReturnBackState() {
  return back_extended;
}