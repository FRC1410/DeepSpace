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

double Limelight::GetTargetXTrans() {
  std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return cameraTransform[0];     //camtran: [x, y, z, pitch, yaw, roll]
}

double Limelight::GetTargetZTrans() {
  std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return -cameraTransform[2];    //camtran: [x, y, z, pitch, yaw, roll]
}

double Limelight::GetTargetAngleTrans() {
  std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return -cameraTransform[4];
}

int Limelight::GetCamtranSize() {
  std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return sizeof(cameraTransform);
}

double Limelight::GetRandyX(){
  return -sin(GetTargetAngleTrans() * (pi / 180) - atan(GetTargetXTrans() / GetTargetZTrans())) * sqrt(pow(GetTargetXTrans(), 2) + pow(GetTargetZTrans(), 2)) - limelight_x_offset;
}

double Limelight::GetRandyZ() {  
  return -cos(GetTargetAngleTrans() * (pi / 180) - atan(GetTargetXTrans() / GetTargetZTrans())) * sqrt(pow(GetTargetXTrans(), 2) + pow(GetTargetZTrans(), 2)) - limelight_z_offset;
}

double Limelight::GetPID(double target, double time_difference) {
  error = target - GetChassisX();
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

double Limelight::GetChassisAngle(){
  return Robot::m_limelight.GetTargetAngleTrans() - limelight_angle_offset;
}

double Limelight::GetChassisX(){
  return Robot::m_limelight.GetTargetXTrans() - (limelight_x_offset * cos(GetChassisAngle()));
}

double Limelight::GetChassisZ(){
  return Robot::m_limelight.GetTargetZTrans() - (limelight_z_offset * sin(GetChassisAngle()));
}