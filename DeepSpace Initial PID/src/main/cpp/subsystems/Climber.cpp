#include "subsystems/Climber.h"
#include "commands/ClimberExtend.h"

Climber::Climber() : Subsystem("ExampleSubsystem") {}

void Climber::InitDefaultCommand() {
  SetDefaultCommand(new ClimberExtend());
}

void Climber::ExtendFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kForward);
}

void Climber::ExtendBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kForward);
}

void Climber::RetractFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kReverse);
}

void Climber::RetractBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kReverse);
}

void Climber::FrontOff(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kOff);
}

void Climber::BackOff(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kOff);
}