#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new Drive());
}

void DriveTrain::TankDrive(double left, double right) {
  m_front.TankDrive(0.9 * left, right);
  m_middle.TankDrive(0.9 * left, right);
  m_back.TankDrive(0.9 * left, right);
}

void DriveTrain::ResetEncoders() {
	m_left_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_right_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_left_middle.GetSensorCollection().SetQuadraturePosition(0, 0);
  m_right_middle.GetSensorCollection().SetQuadraturePosition(0, 0);
}

double DriveTrain::GetDistance() {
	average_distance = ((m_left_middle.GetSensorCollection().GetQuadraturePosition() +  m_right_middle.GetSensorCollection().GetQuadraturePosition()) / 2) * (18.849556 / 4096);
	SmartDashboard::PutNumber("Drivetrain Distance", average_distance);
	return average_distance;
}

double DriveTrain::GetRightDistance(){
  return m_right_middle.GetSensorCollection().GetQuadraturePosition();
}

double DriveTrain::GetLeftDistance(){
  return  m_left_middle.GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::ResetNavX() {
  NavX->Reset();
}

double DriveTrain::GetAngle() {
  return NavX->GetAngle();
}

bool DriveTrain::GetLeftSensor() {
  return !(left_tape_sensor->Get());
}

bool DriveTrain::GetMiddleSensor() {
  return !(middle_tape_sensor->Get());
}

bool DriveTrain::GetRightSensor() {
  return !(right_tape_sensor->Get());
}

double DriveTrain::GetDistancePID(double previous_error, double target, double time_difference) {
  distance_error = target - GetDistance();
  distance_P = drivetrain_distance_kP * distance_error;
  distance_I += drivetrain_distance_kI * distance_error * time_difference;
  distance_D = drivetrain_distance_kD * (distance_error - previous_error) * time_difference;
  previous_error = distance_error;
  return distance_P + distance_I + distance_D;
}

void DriveTrain::ResetDistanceIntegral() {
  distance_I = 0;
}

double DriveTrain::GetGyroPID(double previous_error, double target, double time_difference) {
  gyro_error = target - GetAngle();
  gyro_P = drivetrain_gyro_kP * gyro_error;
  gyro_I += drivetrain_gyro_kI * gyro_error * time_difference;
  gyro_D = drivetrain_gyro_kD * (gyro_error - previous_error) * time_difference;
  return gyro_P + gyro_I + gyro_D;
}

void DriveTrain::ResetGyroIntegral() {
  gyro_I = 0;
}

