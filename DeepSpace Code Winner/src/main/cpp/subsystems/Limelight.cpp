/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include "Robot.h"
#include "RobotMap.h"

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/Smartdashboard.h>

#include <frc/shuffleboard/ShuffleboardTab.h>
#include <frc/shuffleboard/Shuffleboard.h>

Limelight::Limelight() : Subsystem("Limelight") {}

void Limelight::InitDefaultCommand() {}

bool Limelight::GetTarget() {
  frc::Shuffleboard::GetTab("Limelight").Add("Target Value", limelight_table->GetNumber("tv", 0.0));
  return limelight_table->GetNumber("tv", 0.0);
}

double Limelight::GetTargetX() {
 return limelight_table->GetNumber("tx", 0.0);
}

double Limelight::GetTargetY() {
 return limelight_table->GetNumber("ty", 0.0);
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

double Limelight::GetTargetXTrans() {
  //std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return 0;//cameraTransform[0];
}

double Limelight::GetTargetZTrans() {
  //std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return 0;//-cameraTransform[2];
}

double Limelight::GetTargetAngleTrans() {
  //std::vector<double> cameraTransform = limelight_table->GetNumberArray("camtran",std::vector<double>());
  return 0;//-cameraTransform[4];
}

int Limelight::GetCamtranSize() {
  return 0;//sizeof(cameraTransform);
}

double Limelight::GetChassisAngle() {
  return 0;//Robot::m_limelight.GetTargetAngleTrans() - limelight_angle_offset;
}

double Limelight::GetChassisX() {
  return 0;//Robot::m_limelight.GetTargetXTrans() - (limelight_x_offset * cos(GetChassisAngle()));
}

double Limelight::GetChassisZ() {
  return 0;//Robot::m_limelight.GetTargetZTrans() - (limelight_z_offset * sin(GetChassisAngle()));
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