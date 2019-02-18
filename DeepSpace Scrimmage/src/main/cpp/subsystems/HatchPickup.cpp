/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"
#include "commands/HatchPickupRotate.h"
#include "Robot.h"

HatchPickup::HatchPickup() : Subsystem("HatchPickup") {}

void HatchPickup::InitDefaultCommand() {
  SetDefaultCommand(new HatchPickupRotate());
}

void HatchPickup::DisableSafety() {
  m_rotator.SetSafetyEnabled(false);
}

void HatchPickup::RotatePickup(double speed) {
  m_rotator.Set(speed);
  //frc::SmartDashboard::PutNumber("Rotator Speed", speed);
}

void HatchPickup::ResetEncoder() {
  m_rotator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_rotator.GetSensorCollection().SetQuadraturePosition(0, 0);
}

double HatchPickup::GetPosition() {
  return double(m_rotator.GetSensorCollection().GetQuadraturePosition()) / 4096;
}

double HatchPickup::GetPID(double target, double time_difference) {
  error = target - GetPosition();
  P = hatch_pickup_kP * error;
  I += hatch_pickup_kI * error * time_difference;  
  D = hatch_pickup_kD * (error - previous_error) * time_difference;
  previous_error = error;
  return P + I + D;
}

void HatchPickup::ResetIntegral() {
  I = 0;
  previous_error = 0;
}

void HatchPickup::SetState(bool state) {
  raised = state;
}

bool HatchPickup::GetState() {
  return raised;
}