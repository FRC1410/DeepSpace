/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"

Limelight::Limelight() : Subsystem("ExampleSubsystem") {}

void Limelight::InitDefaultCommand() {}

double Limelight::GetTarget() {
 return limelight_table->GetNumber("tv", 0.0);
}

double Limelight::GetTargetX() {
 return limelight_table->GetNumber("tx", 0.0);
}

double Limelight::GetTargetY() {
 return limelight_table->GetNumber("ty", 0.0);
}

double Limelight::GetTargetArea() {
 return limelight_table->GetNumber("ta", 0.0);
}

double Limelight::GetTargetSkew() {
 return limelight_table->GetNumber("ts", 0.0);
}

double Limelight::GetCameraLatency() {
 return limelight_table->GetNumber("tl", 0.0);
}

void Limelight::TurnOffLights() {
  limelight_table->PutNumber("ledMode", 1);
}

void Limelight::TurnOnLights() {
  limelight_table->PutNumber("ledMode", 3);
}

void Limelight::SetPipeline(int profile) {
  limelight_table->PutNumber("pipeline", profile);
}