#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"
#include "Robot.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new Drive());
}

void DriveTrain::SetSpeed(double left, double right) {
  if (abs(left) > 1) {
    current_left_vel = abs(left)/left;
  } else {
    current_left_vel = left;
  }

  if (abs(right) > 1) {
    current_right_vel = abs(right)/right;
  } else {
    current_right_vel = right;
  }

  m_front.TankDrive(current_left_vel, current_right_vel);
  m_middle.TankDrive(current_left_vel, current_right_vel);
  m_back.TankDrive(current_left_vel, current_right_vel);
}

void DriveTrain::Accelerate(double left, double right) {
  left_vel_difference = left - current_left_vel;            //Sets difference for both of the sides of the drivetrain
  right_vel_difference = right - current_right_vel;
  if (abs(left) < 0.3) {
    left_vel_difference = 0;                                //Deadzone
  }
  if (abs(right) < 0.3) {
    right_vel_difference = 0;
  }

  if(abs(left_vel_difference) <= 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) <= 1 / (50 * drivetrain_acceleration_time)) {           //If its close enough, it just sets it.
    SetSpeed(left, right);
  } else if(abs(left_vel_difference) <= 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) > 1 / (50 * drivetrain_acceleration_time)) {   //All this shit is if it doesn't
    if(right_vel_difference > 0) {
      SetSpeed(left, current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else {
      SetSpeed(left, current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    }
  } else if(abs(left_vel_difference) > 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) <= 1 / (50 * drivetrain_acceleration_time)) {
    if(left_vel_difference > 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), right);
    } else {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), right);
    }
  } else {
    if(left_vel_difference > 0 && right_vel_difference > 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else if(left_vel_difference > 0 && right_vel_difference < 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    } else if(left_vel_difference < 0 && right_vel_difference > 0) {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    }
  }
}

void DriveTrain::ResetEncoders() {
	m_left_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_right_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_left_middle.GetSensorCollection().SetQuadraturePosition(0, 0);
  m_right_middle.GetSensorCollection().SetQuadraturePosition(0, 0);
}

double DriveTrain::GetDistance() {
	average_distance = ((m_left_middle.GetSensorCollection().GetQuadraturePosition() +  m_right_middle.GetSensorCollection().GetQuadraturePosition()) / 2) * (6 * pi / 4096);
	SmartDashboard::PutNumber("Drivetrain Distance", average_distance);
	return average_distance;
}

double DriveTrain::GetRightDistance() {
  return m_right_middle.GetSensorCollection().GetQuadraturePosition();
}

double DriveTrain::GetLeftDistance() {
  return m_left_middle.GetSensorCollection().GetQuadraturePosition();
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

