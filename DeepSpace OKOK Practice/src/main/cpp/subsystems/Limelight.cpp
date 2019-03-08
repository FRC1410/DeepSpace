/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include "Robot.h"
#include "RobotMap.h"

Limelight::Limelight() : Subsystem("ExampleSubsystem") {}

void Limelight::InitDefaultCommand() {}

bool Limelight::GetTarget() {
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
 return limelight_table->GetNumber("tl", 0.0) / 1000 + 0.011;
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

double Limelight::GetTargetXTrans() {
  return cameraTransform[0];
}

double Limelight::GetTargetZTrans() {
  return -cameraTransform[2];
}

double Limelight::GetTargetAngleTrans() {
  return -cameraTransform[4];
}

int Limelight::GetCamtranSize() {
  return sizeof(cameraTransform);
}

double Limelight::GetChassisAngle() {
  return Robot::m_limelight.GetTargetAngleTrans() - limelight_angle_offset;
}

double Limelight::GetChassisX() {
  return Robot::m_limelight.GetTargetXTrans() - (limelight_x_offset * cos(GetChassisAngle()));
}

double Limelight::GetChassisZ() {
  return Robot::m_limelight.GetTargetZTrans() - (limelight_z_offset * sin(GetChassisAngle()));
}

double Limelight::GetPID(double position, double time_difference) {
  error = -position;
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