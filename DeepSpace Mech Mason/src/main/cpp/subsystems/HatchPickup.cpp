#include "subsystems/HatchPickup.h"
#include "commands/HatchPickupRotate.h"
#include "Robot.h"

HatchPickup::HatchPickup() : Subsystem("HatchPickup") {}

void HatchPickup::InitDefaultCommand() {
  SetDefaultCommand(new HatchPickupRotate());
}

void HatchPickup::RotatePickup(double speed) {
  m_rotator.Set(speed);
frc::SmartDashboard::PutNumber("Rotator Speed", speed);
}

void HatchPickup::ResetEncoder() {
	m_rotator.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_rotator.GetSensorCollection().SetQuadraturePosition(0, 0);
}

double HatchPickup::GetPosition(){
  return m_rotator.GetSensorCollection().GetQuadraturePosition();
}

double HatchPickup::GetPID(double previous_error, double target, double time_difference) {
  error = target - GetPosition();
  P = hatch_pickup_kP * error;
  I += hatch_pickup_kI * error * time_difference;   //could be wrong syntax :(
  D = hatch_pickup_kD * (error - previous_error) * time_difference;
  previous_error = error;
  return P + I + D;
  
}

void HatchPickup::ResetIntegral() {
  I = 0;
}