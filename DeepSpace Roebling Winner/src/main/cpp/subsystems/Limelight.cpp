/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"

Limelight::Limelight() : Subsystem("Limelight") {}

void Limelight::InitDefaultCommand() {}

bool Limelight::GetTarget() {
  shuffleboard_tv.SetBoolean(limelight_table->GetNumber("tv", 0.0));
  return limelight_table->GetNumber("tv", 0.0);
}

double Limelight::GetTargetX() {
  shuffleboard_tx.SetDouble(limelight_table->GetNumber("tx", 0.0));
  return limelight_table->GetNumber("tx", 0.0);
}

double Limelight::GetTargetArea() {
  shuffleboard_ta.SetDouble(limelight_table->GetNumber("ta", 0.0));
  return limelight_table->GetNumber("ta", 0.0);
}

void Limelight::SetPipeline(int profile) {
  pipeline = profile;
  limelight_table->PutNumber("pipeline", pipeline);
}

int Limelight::GetPipeline() {
  return pipeline;
}

void Limelight::SetTargetFound(bool target) {
  target_found = target;

  frc::SmartDashboard::PutNumber("Vision Target", target_found);
  shuffleboard_vision.SetBoolean(target);
}

bool Limelight::GetTargetFound() {
  return target_found;
}

double Limelight::GetAnglePID(double target, double time_difference) {
  angle_error = target - GetTargetX();
  angle_P = input_angle_kP * angle_error;
  angle_I += input_angle_kI * angle_error * time_difference;
  angle_D = input_angle_kD * (angle_error - angle_previous_error) * time_difference;
  angle_previous_error = angle_error;
  return angle_P + angle_I + angle_D;
}

double Limelight::ResetAngleIntegral() {
  angle_I = 0;
  angle_previous_error = 0;
}

double Limelight::GetAreaPID(double target, double time_difference) {
  area_error = sqrt(target) - sqrt(GetTargetArea());
  if (GetTargetArea() < limelight_large_area) {
    area_P = input_area_kP * area_error;
    area_I = input_area_kI * area_error * time_difference;
    area_D = input_area_kD * (area_error - area_previous_error) * time_difference;
    area_previous_error = area_error;
    return area_P + area_I + area_D;
  } else {
    ResetAreaIntegral();
    return 0;
  }
}

double Limelight::ResetAreaIntegral() {
  area_I = 0;
  area_previous_error = 0;
}

double Limelight::GetDistancePID(double target, double time_difference) {
  distance_error = sqrt(abs(target - GetTargetArea()));
  distance_P = input_distance_kP * distance_error;
  distance_I = input_distance_kI * distance_error * time_difference;
  distance_D = input_distance_kD * (distance_error - distance_previous_error) * time_difference;
  distance_previous_error = distance_error;
  return area_P + area_I + area_D;
}

double Limelight::ResetDistanceIntegral() {
  distance_I = 0;
  distance_previous_error = 0;
}

void Limelight::SetPIDConstants() {
  if (shuffleboard_area_PID.GetBoolean(false) == was_area) {
    if (was_area == false) {
      input_angle_kP = shuffleboard_P_input.GetDouble(input_area_kP);
      input_angle_kI = shuffleboard_I_input.GetDouble(input_area_kI);
      input_angle_kD = shuffleboard_D_input.GetDouble(input_area_kD);
    } else {
      input_area_kP = shuffleboard_P_input.GetDouble(input_area_kP);
      input_area_kI = shuffleboard_I_input.GetDouble(input_area_kI);
      input_area_kD = shuffleboard_D_input.GetDouble(input_area_kD);
    }
  } else {
    if (was_area == false) {
      shuffleboard_P_input.SetDouble(input_area_kP);
      shuffleboard_I_input.SetDouble(input_area_kI);
      shuffleboard_D_input.SetDouble(input_area_kD);
    } else {
      shuffleboard_P_input.SetDouble(input_angle_kP);
      shuffleboard_I_input.SetDouble(input_angle_kI);
      shuffleboard_D_input.SetDouble(input_angle_kD);
    }
  }

  if (shuffleboard_area_PID.GetBoolean(false) == false) {
    shuffleboard_P.SetDouble(input_angle_kP);
    shuffleboard_I.SetDouble(input_angle_kI);
    shuffleboard_D.SetDouble(input_angle_kD);
  } else {
    shuffleboard_P.SetDouble(input_area_kP);
    shuffleboard_I.SetDouble(input_area_kI);
    shuffleboard_D.SetDouble(input_area_kD);
  }

  was_area = shuffleboard_area_PID.GetBoolean(false);
}

void Limelight::SetDistancePIDConstants(double kP, double kI, double kD) {
  input_distance_kP = kP;
  input_distance_kI = kI;
  input_distance_kD = kD;
}