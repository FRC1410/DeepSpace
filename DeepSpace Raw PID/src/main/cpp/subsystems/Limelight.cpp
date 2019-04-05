/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include "Robot.h"
#include "RobotMap.h"

Limelight::Limelight() : Subsystem("Limelight") {}

void Limelight::InitDefaultCommand() {}

bool Limelight::GetTarget() {
 return limelight_table->GetNumber("tv", 0.0);
}

double Limelight::GetTargetX() {
 return limelight_table->GetNumber("tx", 0.0);
}

double Limelight::GetTargetArea() {
 return limelight_table->GetNumber("ta", 0.0);
}

void Limelight::TurnOffLights() {
  limelight_table->PutNumber("ledMode", 1);
}

void Limelight::TurnOnLights() {
  limelight_table->PutNumber("ledMode", 3);
}

void Limelight::SetPipeline(int profile) {
  current_profile = profile;
  limelight_table->PutNumber("pipeline", profile);
}

int Limelight::GetPipeline() {
  return current_profile;
}

double Limelight::GetPID(double position, double time_difference) {
  error = GetTargetX() - position;
  P = limelight_kP * error;
  I += limelight_kI * error * time_difference;
  D = limelight_kD * (error - previous_error) * time_difference;
  previous_error = error;
  return P + I + D;
}

double Limelight::ResetIntegral() {
  I = 0;
  previous_error = 0;
}