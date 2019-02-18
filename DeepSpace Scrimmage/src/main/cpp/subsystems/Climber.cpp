/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Climber.h"
#include "commands/ClimberExtend.h"
#include "Robot.h"

Climber::Climber() : Subsystem("Climber") {}

void Climber::InitDefaultCommand() {
  SetDefaultCommand(new ClimberExtend());
}

void Climber::ExtendFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kReverse);
  front_extended = true;
  //frc::SmartDashboard::PutBoolean("Climber Front State", true);
}

void Climber::ExtendBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kForward);
  back_extended = true;
  //frc::SmartDashboard::PutBoolean("Climber Back State", true);
}

void Climber::RetractFront(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kForward);
  front_extended = false;
  //frc::SmartDashboard::PutBoolean("Climber Front State", false);
}

void Climber::RetractBack(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kReverse);
  back_extended = false;
  //frc::SmartDashboard::PutBoolean("Climber Back State", false);
}

void Climber::FrontOff(){
  climber_front_solenoid.Set(frc::DoubleSolenoid::kOff);
  front_extended = false;
  //frc::SmartDashboard::PutBoolean("Climber Front State", false);
}

void Climber::BackOff(){
  climber_back_solenoid.Set(frc::DoubleSolenoid::kOff);
  back_extended = false;
  //frc::SmartDashboard::PutBoolean("Climber Back State", false);
}

bool Climber::GetFrontState() {
  return front_extended;
}

bool Climber::GetBackState() {
  return back_extended;
}