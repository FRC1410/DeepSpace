/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "commands/Drive.h"
#include "Robot.h"
#include "DataTables.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {}

void DriveTrain::InitDefaultCommand() {
  SetDefaultCommand(new Drive());
}

void DriveTrain::DisableSafety() {
  m_front.SetSafetyEnabled(false);
  m_middle.SetSafetyEnabled(false);
  m_back.SetSafetyEnabled(false);
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

  frc::SmartDashboard::PutNumber("Left Drivetrain Power", current_left_vel);
  frc::SmartDashboard::PutNumber("Right Drivetrain Power", current_right_vel);
}

void DriveTrain::SetCurvedSpeed(double left, double right) {
  if (left == 0) {
    current_left_vel = 0;
  } else if (abs(left) < drivetrain_friction_deadband) {
    current_left_vel = (abs(left) / left) * sqrt((pow(drivetrain_friction, 2) / drivetrain_friction_deadband) * abs(left));
  } else {
    current_left_vel = ((1 - drivetrain_friction) / (1 - drivetrain_friction_deadband)) * (left - (abs(left) / left) * drivetrain_friction_deadband) + (abs(left) / left) * drivetrain_friction;
  }

  if (right == 0) {
    current_right_vel = 0;
  } else if (abs(right) < drivetrain_friction_deadband) {
    current_right_vel = (abs(right) / right) * sqrt((pow(drivetrain_friction, 2) / drivetrain_friction_deadband) * abs(right));
  } else {
    current_right_vel = ((1 - drivetrain_friction) / (1 - drivetrain_friction_deadband)) * (right - (abs(right) / right) * drivetrain_friction_deadband) + (abs(right) / right) * drivetrain_friction;
  }

  SetSpeed(current_left_vel, current_right_vel);
}

double DriveTrain::GetCurvedSpeed(double value) {
  if (value == 0) {
    return 0;
  } else if (abs(value) < drivetrain_friction) {
    return (abs(value) * value * drivetrain_friction_deadband) / pow(drivetrain_friction, 2);
  } else {
    return ((1 - drivetrain_friction_deadband) / (1 - drivetrain_friction)) * (value - (abs(value) / value) * drivetrain_friction) + (abs(value) / value) * drivetrain_friction_deadband;
  }
}

void DriveTrain::Accelerate(double left, double right) {
  left_vel_difference = left - current_left_vel;
  right_vel_difference = right - current_right_vel;
  if (abs(left) < 0.3) {
    left_vel_difference = 0;
  }
  if (abs(right) < 0.3) {
    right_vel_difference = 0;
  }

  if (abs(left_vel_difference) <= 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) <= 1 / (50 * drivetrain_acceleration_time)) {
    SetSpeed(left, right);
  } else if (abs(left_vel_difference) <= 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) > 1 / (50 * drivetrain_acceleration_time)) {
    if (right_vel_difference > 0) {
      SetSpeed(left, current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else {
      SetSpeed(left, current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    }
  } else if (abs(left_vel_difference) > 1 / (50 * drivetrain_acceleration_time) && abs(right_vel_difference) <= 1 / (50 * drivetrain_acceleration_time)) {
    if (left_vel_difference > 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), right);
    } else {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), right);
    }
  } else {
    if (left_vel_difference > 0 && right_vel_difference > 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else if (left_vel_difference > 0 && right_vel_difference < 0) {
      SetSpeed(current_left_vel + (1 / (50 * drivetrain_acceleration_time)), current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    } else if (left_vel_difference < 0 && right_vel_difference > 0) {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), current_right_vel + (1 / (50 * drivetrain_acceleration_time)));
    } else {
      SetSpeed(current_left_vel - (1 / (50 * drivetrain_acceleration_time)), current_right_vel - (1 / (50 * drivetrain_acceleration_time)));
    }
  }
}

void DriveTrain::ResetEncoders() {
  m_left_back.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_right_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  m_left_back.GetSensorCollection().SetQuadraturePosition(0, 0);
  m_right_middle.GetSensorCollection().SetQuadraturePosition(0, 0);
}

double DriveTrain::GetDistance() {
  average_distance = (double(m_right_middle.GetSensorCollection().GetQuadraturePosition() - m_left_back.GetSensorCollection().GetQuadraturePosition()) / 2) * (6 * pi / 1024);
  SmartDashboard::PutNumber("Drivetrain Distance", average_distance);
  return average_distance;
}

double DriveTrain::GetRightDistance() {
  return m_right_middle.GetSensorCollection().GetQuadraturePosition();
}

double DriveTrain::GetLeftDistance() {
  return m_left_back.GetSensorCollection().GetQuadraturePosition();
}

void DriveTrain::ResetNavX() {
  NavX->Reset();
}

double DriveTrain::GetAngle() {
  return NavX->GetAngle() + 180;
}

double DriveTrain::GetDistancePID(double target, double time_difference) {
  distance_error = target - GetDistance();
  distance_P = drivetrain_distance_kP * distance_error;
  distance_I += drivetrain_distance_kI * distance_error * time_difference;
  distance_D = drivetrain_distance_kD * (distance_error - distance_previous_error) * time_difference;
  distance_previous_error = distance_error;
	frc::SmartDashboard::PutNumber("Distance PID", distance_P + distance_I + distance_D);
  return distance_P + distance_I + distance_D;
}

void DriveTrain::ResetDistanceIntegral() {
  distance_I = 0;
}

double DriveTrain::GetGyroPID(double target, double time_difference) {
  gyro_error = target - GetAngle();
  gyro_P = drivetrain_gyro_kP * gyro_error;
  gyro_I += drivetrain_gyro_kI * gyro_error * time_difference;
  gyro_D = drivetrain_gyro_kD * (gyro_error - gyro_previous_error) * time_difference;
  gyro_previous_error = gyro_error;
	frc::SmartDashboard::PutNumber("Gyro PID", gyro_P + gyro_I + gyro_D);
  return gyro_P + gyro_I + gyro_D;
}

void DriveTrain::ResetGyroIntegral() {
  gyro_I = 0;
}

double DriveTrain::FresnelSineCalc(double input) {
	if (abs(input) < 100) {
		return FresnelSineData[int(abs(input) / increment)] * (1 - (abs(input / increment) - int(abs(input / increment)))) + FresnelSineData[int(abs(input) / increment) + 1] * (abs(input / increment) - int(abs(input / increment)));
	} else {
		return sqrt(pi / 8);
	}
}

double DriveTrain::FresnelCosineCalc(double input) {
	if (abs(input) < 100) {
		return FresnelCosineData[int(abs(input) / increment)] * (1 - (abs(input / increment) - int(abs(input / increment)))) + FresnelCosineData[int(abs(input) / increment) + 1] * (abs(input / increment) - int(abs(input / increment)));
	} else {
		return sqrt(pi / 8);
	}
}

double DriveTrain::CalcPathX(double skew, double time) {
	return ((c[18] * c[23] - c[17] * c[22]) / c[5]) + ((c[19] * c[15] - c[20] * c[16]) / c[7]) + ((c[1] * c[3]) - c[0]) * cos(c[21]) - (c[1] * c[3]) + ((c[1] / c[2]) + c[0]) * cos(c[13]) - (c[1] / c[2]) * cos(a);
}

double DriveTrain::CalcPathZ(double skew, double time) {
	return ((c[17] * c[23] + c[18] * c[22]) / c[5]) + ((c[20] * c[15] + c[19] * c[16]) / c[7]) - ((c[1] * c[3]) - c[0]) * sin(c[21]) - ((c[1] / c[2]) + c[0]) * sin(c[13]) + (c[1] / c[2]) * sin(a);
}

void DriveTrain::SetVars(double time) {
	path_calcs++;
	h = ((2 * a + (r2 - r1) * skew) / time) - r2;
	c[1] = (v1 - v2) / time;
	c[2] = (h - r2) / (time - skew);
	c[3] = skew / (h - r1);
	if (drivetrain_max_speed - (h * c[0]) < v1 - (c[1] * skew)) {
		i1 = (v1 - drivetrain_max_speed + c[0] * r1) / (c[1] - (c[0] / c[3]));
		i2 = (v1 - drivetrain_max_speed + c[0] * r2 + (c[0] * c[2] * time)) / (c[0] * c[2] + c[1]);
	} else {
		i2 = skew;
		i1 = skew;
	}
	c[4] = pow(r1, 2) * c[3] / 2;
	c[5] = sqrt(0.5 / c[3]);
	c[6] = c[5] * (i1 + r1 * c[3]);
	c[7] = sqrt(c[2] / 2);
	c[8] = v1 + r1 * c[1] * c[3];
	c[9] = (skew + r1 * c[3]) * c[5];
	c[10] = v2 - (c[1] * r2 / c[2]);
	c[11] = (time - i2 + (r2 / c[2])) * c[7];
	c[12] = (time - skew + (r2 / c[2])) * c[7];
	c[13] = (i2 - time) * (r2 + (c[2] / 2) * (time - i2))+ a;
	c[14] = sqrt(c[4]);
	c[15] = (c[10] - drivetrain_max_speed) * FresnelCosineCalc(c[11]) + drivetrain_max_speed * FresnelCosineCalc(c[12]) - c[10] * FresnelCosineCalc(r2 * c[7] / c[2]);
	c[16] = (c[10] - drivetrain_max_speed) * FresnelSineCalc(c[11]) + drivetrain_max_speed * FresnelSineCalc(c[12]) - c[10] * FresnelSineCalc(r2 * c[7] / c[2]);
	c[17] = drivetrain_max_speed * FresnelCosineCalc(c[9]) + (c[8] - drivetrain_max_speed) * FresnelCosineCalc(c[6]) - c[8] * FresnelCosineCalc(c[14]);
	c[18] = drivetrain_max_speed * FresnelSineCalc(c[9]) + (c[8] - drivetrain_max_speed) * FresnelSineCalc(c[6]) - c[8] * FresnelSineCalc(c[14]);
	c[19] = sin(a + (pow(r2, 2) / (2 * c[2])));
	c[20] = cos(a + (pow(r2, 2) / (2 * c[2])));
	c[21] = (pow(i1, 2) / (2 * c[3])) + r1 * i1;
	c[22] = sin(c[4]);
	c[23] = cos(c[4]);
}

double DriveTrain::CalcSkew(double time, double aspect) {
	lower_skew = 0.01 * time;
	upper_skew = 0.99 * time;
	skew = lower_skew;
	SetVars(time);
	if (CalcPathX(skew, time) > CalcPathZ(skew, time) * aspect) {
		skew = upper_skew;
		SetVars(time);
		if (CalcPathX(skew, time) < CalcPathZ(skew, time) * aspect) {
			skew_counter = counter;
			calced_x = CalcPathX(skew, time);
			calced_z = CalcPathZ(skew, time);
			while (abs(calced_x - calced_z * aspect) > drivetrain_motion_profile_tolerance) {
				if (counter - skew_counter >= 20) {
					break;
				}
				skew = (lower_skew + upper_skew) / 2;
				SetVars(time);
				calced_x = CalcPathX(skew, time);
				calced_z = CalcPathZ(skew, time);
				if (calced_x > calced_z * aspect) {
					lower_skew = skew;
				} else {
					upper_skew = skew;
				}
				counter++;
			}
			if (counter - skew_counter < 20) {
				frc::SmartDashboard::PutNumber("Skewed", skew);
				return skew;
			} else {
				return -1;
			}
		} else {
			return -2;
		}
	} else {
		return -3;
	}
}

bool DriveTrain::CalculateRawPath(double target_x, double target_z, double angle, double final_velocity, double final_rotational_speed) {
	skew_counter = 0;
	path_calcs = 0;
	counter = 0;
	tolerance = drivetrain_motion_profile_tolerance;
	frc::SmartDashboard::PutNumber("Failure", 0);
	distance_reference = GetDistance();
	angle_reference = GetAngle();
	initial_rotational_speed = (Robot::m_drivetrain.GetCurvedSpeed(current_left_vel) - Robot::m_drivetrain.GetCurvedSpeed(current_right_vel)) * ((drivetrain_max_speed * drivetrain_driftiness) / (2 * drivetrain_radius)) / angle;
	if (abs(initial_rotational_speed) < 0.1) {
		initial_rotational_speed = 0;
	}
	initial_velocity = (Robot::m_drivetrain.GetCurvedSpeed(current_left_vel) + Robot::m_drivetrain.GetCurvedSpeed(current_right_vel)) * drivetrain_max_speed / 2;
	if (abs(initial_velocity) < 1) {
		initial_velocity = 0;
	}
	frc::SmartDashboard::PutNumber("Initial rot", initial_rotational_speed);
	frc::SmartDashboard::PutNumber("Initial vel", initial_velocity);
	if (angle == 0 || initial_rotational_speed / angle < 0 || final_rotational_speed / angle < 0 || abs(angle) > 180) {
		frc::SmartDashboard::PutNumber("Failure", 1);
		goto jumper;
	}
	if ((initial_velocity > 0 && final_velocity < 0) || (initial_velocity < 0 && final_velocity > 0)) {
		frc::SmartDashboard::PutNumber("Failure", 2);
		goto jumper;
	}
	if (initial_velocity < 0 || final_velocity < 0) {
		inverted_velocity = true;
		target_x = -target_x;
		target_z = -target_z;
	} else {
		inverted_velocity = false;
	}
	if (angle < 0) {
		inverted_direction = true;
		target_x = -target_x;
	} else {
		inverted_direction = false;
	}
	a = abs(angle * pi / 180);
	r1 = abs(initial_rotational_speed);
	r2 = abs(final_rotational_speed * pi / 180);
	v1 = abs(initial_velocity);
	v2 = abs(final_velocity);

	c[0] = drivetrain_radius / drivetrain_driftiness;
	if (r1 > r2) {
		lower_time = (2 * a) / (r1 + (drivetrain_max_speed / c[0]));
		upper_time = a / r1;
	} else if (r2 < r1) {
		lower_time = (2 * a) / (r2 + (drivetrain_max_speed / c[0]));
		upper_time = a / r2;
	} else {
		lower_time = (2 * a) / (drivetrain_max_speed / c[0]);
		upper_time = 15;
	}
	if (CalcSkew(lower_time, target_x / target_z) > 0 && CalcPathX(CalcSkew(lower_time, target_x / target_z), lower_time) < target_x && CalcSkew(upper_time, target_x / target_z) > 0 && CalcPathX(CalcSkew(upper_time, target_x / target_z), upper_time) > target_x) {
		if (target_x / target_z < 1) {
			tolerance = tolerance * target_x / target_z;
		}
		calc_time = (lower_time + upper_time) / 2;
		calc_skew = CalcSkew(calc_time, target_x / target_z);
		if (calc_skew < 0) {
			frc::SmartDashboard::PutNumber("Failure", 27);
			goto jumper;
		}
		dist = CalcPathX(calc_skew, calc_time) - target_x;
		do {
			if (dist > 0) {
				upper_time = calc_time;
			}
			else {
				lower_time = calc_time;
			}
			calc_time = (lower_time + upper_time) / 2;
			calc_skew = CalcSkew(calc_time, target_x / target_z);
			if (calc_skew < 0) {
				frc::SmartDashboard::PutNumber("Failure", 33);
				goto jumper;
			}
			dist = CalcPathX(calc_skew, calc_time) - target_x;
			if (calc_skew < 0 || path_calcs > 379) {
				frc::SmartDashboard::PutNumber("Failure", 67);
				goto jumper;
			}
		} while (abs(dist) > tolerance);
		stable_skew = calc_skew;
		stable_time = calc_time;
		frc::SmartDashboard::PutNumber("Stable Time", stable_time);
		frc::SmartDashboard::PutNumber("Stable Skew", stable_skew);
		stable_v1 = v1;
		stable_r1 = r1;
		stable_r2 = r2;
		stable_c1 = c[1];
		stable_c2 = c[2];
		stable_c3 = c[3];
		stable_i1 = i1;
		stable_i2 = i2;
		stable_h = h;
		stable_a = a;
		stable_inverted_direction = inverted_direction;
		stable_inverted_velocity = inverted_velocity;
		return true;
	} else {
		frc::SmartDashboard::PutBoolean("Failure", 3);
		jumper:
			return false;
	}
}

bool DriveTrain::CalculatePath(double x_displacement, double z_displacement, double angle, double final_velocity, double final_rotational_speed) {
	if (x_displacement > 0) {
		CalculateRawPath(sqrt(pow(x_displacement, 2) + pow(z_displacement, 2)) * sin(pi / 2 - atan(z_displacement / x_displacement) - GetAngle() * pi / 180), sqrt(pow(x_displacement, 2) + pow(z_displacement, 2)) * cos(pi / 2 - atan(z_displacement / x_displacement) - GetAngle() * pi / 180), angle, final_velocity, final_rotational_speed);
		return true;
	} else if (x_displacement < 0) {
		CalculateRawPath(sqrt(pow(x_displacement, 2) + pow(z_displacement, 2)) * sin(3 * pi / 2 - atan(z_displacement / x_displacement) - GetAngle() * pi / 180), sqrt(pow(x_displacement, 2) + pow(z_displacement, 2)) * cos(3 * pi / 2 - atan(z_displacement / x_displacement) - GetAngle() * pi / 180), angle, final_velocity, final_rotational_speed);
		return true;
	} else {
		return false;
	}
}

void DriveTrain::FollowPath(double time, double time_difference) {
	if (time < stable_i1) {
		current_left_vel = ((stable_v1 - stable_c1 * time) + c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
		current_right_vel = ((stable_v1 - stable_c1 * time) - c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
		distance = time * (stable_v1 - (stable_c1 * time) / 2);
		direction = (180 / pi) * time * (stable_r1 + (time / (2 * stable_c3)));
	} else if (time < stable_skew) {
		current_left_vel = 1;
		current_right_vel = 1 - (2 * c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
		distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((time - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - c[0] * (stable_r1 + (time / stable_c3)));
		direction = (180 / pi) * time * (stable_r1 + (time / (2 * stable_c3)));
	} else if (time < stable_i2) {
		current_left_vel = 1;
		current_right_vel = 1 - (2 * c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
		distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((stable_skew - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - (c[0] * stable_h)) + ((time - stable_skew) / 2) * ((2 * drivetrain_max_speed) + c[0] * (stable_c2 * (time - stable_time) - stable_r2 - stable_h));
		direction = (180 / pi) * (stable_a - (stable_time - time) * ((stable_time - time) * (stable_c2 / 2) + stable_r2));
	} else {
		current_left_vel = ((stable_v1 - stable_c1 * time) + c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
		current_right_vel = ((stable_v1 - stable_c1 * time) - c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
		distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((stable_skew - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - (c[0] * stable_h)) + ((stable_i2 - stable_skew) / 2) *  ((2 * drivetrain_max_speed) + c[0] * (stable_c2 * (stable_i2 - stable_time) - stable_r2 - stable_h)) + (time - stable_i2) * (stable_v1 - (stable_c1 * (time + stable_i1) / 2));
		direction = (180 / pi) * (stable_a - (stable_time - time) * ((stable_time - time) * (stable_c2 / 2) + stable_r2));
	}
	if (stable_inverted_direction == true) {
		hold = current_left_vel;
		current_left_vel = current_right_vel;
		current_right_vel = hold;
		direction = -direction;
	}
	if (stable_inverted_velocity == true) {
		hold = current_left_vel;
		current_left_vel = -current_right_vel;
		current_right_vel = -hold;
		distance = -distance;
	}
	frc::SmartDashboard::PutNumber("Distance Target", distance);
	frc::SmartDashboard::PutNumber("Non PID Left", current_left_vel);
	frc::SmartDashboard::PutNumber("Non PID Right", current_right_vel);
	
	distance_PID = GetDistancePID(distance + distance_reference, time_difference);
	gyro_PID =  GetGyroPID(direction + angle_reference, time_difference);

	if (time < stable_time) {
		SetSpeed(current_left_vel + distance_PID + gyro_PID, current_right_vel + distance_PID - gyro_PID);
	}
}

double DriveTrain::GetPathTime() {
	return stable_time;
}

void DriveTrain::ResetTime() {
	stable_time = 0;
}