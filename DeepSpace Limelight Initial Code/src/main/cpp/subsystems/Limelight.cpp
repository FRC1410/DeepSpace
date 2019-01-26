#include "subsystems/Limelight.h"

Limelight::Limelight() : Subsystem("ExampleSubsystem") {}

void Limelight::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

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