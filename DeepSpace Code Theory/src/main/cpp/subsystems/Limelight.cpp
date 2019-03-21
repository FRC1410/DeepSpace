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
 return limelight_table->GetNumber("tx", 0.0) * pi / 180;
}

double Limelight::GetTargetY() {
 return limelight_table->GetNumber("ty", 0.0) * pi / 180;
}

double Limelight::GetTargetWidth() {
 return limelight_table->GetNumber("thor", 0.0);
}

double Limelight::GetTargetHeight() {
 return limelight_table->GetNumber("tvert", 0.0);
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
  current_profile = profile;
  limelight_table->PutNumber("pipeline", profile);
}

int Limelight::GetPipeline() {
  return current_profile;
}

double Limelight::GetLimelightX() {
  return (abs(limelight_y_offset / (tan(GetTargetY()) + (GetTargetHeight() / 518.2194299849982217004254843614))) - abs(1.3770900222994277873742407380537 * sin(Robot::m_drivetrain.GetTargetAngle() * pi / 180))) * (tan(GetTargetX()) - ((GetTargetWidth() / 558.75149777245676271014114622941) * (abs(Robot::m_drivetrain.GetTargetAngle()) / Robot::m_drivetrain.GetTargetAngle()))) + ((7.3133853030556433373076713353129 * cos(Robot::m_drivetrain.GetTargetAngle() * pi / 180)) * (abs(Robot::m_drivetrain.GetTargetAngle()) / Robot::m_drivetrain.GetTargetAngle()));
}

double Limelight::GetLimelightZ() {
  return abs(limelight_y_offset / (tan(GetTargetY()) + (GetTargetHeight() / 518.2194299849982217004254843614))) + abs(5.9362952807562155499334305972592 * sin(Robot::m_drivetrain.GetTargetAngle() * pi / 180));
}

double Limelight::GetChassisAngle() {
  return (Robot::m_drivetrain.GetTargetAngle() + limelight_angle_offset) * pi / 180;
}

double Limelight::GetChassisX() {
  return (sqrt(pow(GetLimelightX(), 2) + pow(GetLimelightZ(), 2)) * sin((Robot::m_drivetrain.GetTargetAngle() * pi / 180) + Robot::m_macro_superstructure.GetDirection(GetLimelightX(), GetLimelightX())));// - (limelight_x_offset * cos(GetChassisAngle()));
}

double Limelight::GetChassisZ() {
  return (sqrt(pow(GetLimelightX(), 2) + pow(GetLimelightZ(), 2)) * cos((Robot::m_drivetrain.GetTargetAngle() * pi / 180) + Robot::m_macro_superstructure.GetDirection(GetLimelightX(), GetLimelightX())));// - (limelight_z_offset * sin(GetChassisAngle()));
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