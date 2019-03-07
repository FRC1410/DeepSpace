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

void DriveTrain::SetSpeed(double left, double right) {
	if (abs(left) > 1) {
		left_velocity = abs(left)/left;
	} else {
		left_velocity = left;
	}

	if (abs(right) > 1) {
		right_velocity = abs(right)/right;
	} else {
		right_velocity = right;
	}

	m_tank.TankDrive(left_velocity, right_velocity);
}

void DriveTrain::SetCurvedSpeed(double left, double right) {
	if (left == 0) {
		left_velocity = 0;
	} else if (abs(left) < drivetrain_friction_deadband) {
		left_velocity = (abs(left) / left) * sqrt((pow(drivetrain_friction, 2) / drivetrain_friction_deadband) * abs(left));
	} else {
		left_velocity = ((1 - drivetrain_friction) / (1 - drivetrain_friction_deadband)) * (left - (abs(left) / left) * drivetrain_friction_deadband) + (abs(left) / left) * drivetrain_friction;
	}

	if (right == 0) {
		right_velocity = 0;
	} else if (abs(right) < drivetrain_friction_deadband) {
		right_velocity = (abs(right) / right) * sqrt((pow(drivetrain_friction, 2) / drivetrain_friction_deadband) * abs(right));
	} else {
		right_velocity = ((1 - drivetrain_friction) / (1 - drivetrain_friction_deadband)) * (right - (abs(right) / right) * drivetrain_friction_deadband) + (abs(right) / right) * drivetrain_friction;
	}

	SetSpeed(right_velocity, right_velocity);
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

double DriveTrain::ApplyAcceleration(double current_speed, double target_speed, double time_difference) {
  current_speed = Robot::m_macro_superstructure.CapValue(current_speed);
  target_speed = Robot::m_macro_superstructure.CapValue(target_speed);
  if (abs(target_speed - current_speed) < (time_difference / drivetrain_acceleration_time)) {
    return target_speed;
  } else {
    return current_speed + (time_difference / drivetrain_acceleration_time) * (abs(target_speed - current_speed) / (target_speed - current_speed));
  }
}

void DriveTrain::Accelerate(double left, double right, double time_difference) {
	SetSpeed(ApplyAcceleration(left_velocity, left, time_difference), ApplyAcceleration(right_velocity, right, time_difference));
}

void DriveTrain::CurvedAccelerate(double left, double right, double time_difference) {
	SetCurvedSpeed(ApplyAcceleration(GetCurvedSpeed(left_velocity), left, time_difference), ApplyAcceleration(GetCurvedSpeed(right_velocity), right, time_difference));
}

void DriveTrain::ResetEncoders() {
	m_left_back.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
	m_right_middle.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, 0, 0);
  initial_left_position = m_left_back.GetSensorCollection().GetQuadraturePosition();
  initial_right_position = m_right_middle.GetSensorCollection().GetQuadraturePosition();
}

double DriveTrain::GetLeftDistance() {
	return m_left_back.GetSensorCollection().GetQuadraturePosition() - initial_left_position;
}

double DriveTrain::GetRightDistance() {
  return m_right_middle.GetSensorCollection().GetQuadraturePosition() - initial_right_position;
}

double DriveTrain::GetDistance() {
  return ((GetLeftDistance() - GetRightDistance()) / 2) * (6 * pi / 4096);
}

void DriveTrain::SetX(double value) {
  x_position = value;
}

void DriveTrain::SetZ(double value) {
  z_position = value;
}

void DriveTrain::IncrementX(double increment) {
  x_position += increment;
}

void DriveTrain::IncrementZ(double increment) {
  z_position += increment;
}

double DriveTrain::GetX() {
  return x_position;
}

double DriveTrain::GetZ() {
  return z_position;
}

void DriveTrain::ResetNavX(double start) {
  initial_angle = start;
	NavX->Reset();
}

double DriveTrain::GetAngle() {
  return NavX->GetAngle() + initial_angle;
}

double DriveTrain::GetDistancePID(double target, double time_difference) {
	distance_error = target - GetDistance();
	distance_P = drivetrain_distance_kP * distance_error;
	distance_I += drivetrain_distance_kI * distance_error * time_difference;
	distance_D = drivetrain_distance_kD * (distance_error - distance_previous_error) * time_difference;
	distance_previous_error = distance_error;
	return distance_P + distance_I + distance_D;
}

void DriveTrain::ResetDistanceIntegral() {
  distance_I = 0;
  distance_previous_error = 0;
}

double DriveTrain::GetGyroPID(double target, double time_difference) {
	gyro_error = target - GetAngle();
	gyro_P = drivetrain_gyro_kP * gyro_error;
	gyro_I += drivetrain_gyro_kI * gyro_error * time_difference;
	gyro_D = drivetrain_gyro_kD * (gyro_error - gyro_previous_error) * time_difference;
	gyro_previous_error = gyro_error;
	return gyro_P + gyro_I + gyro_D;
}

void DriveTrain::ResetGyroIntegral() {
  gyro_I = 0;
  gyro_previous_error = 0;
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
  distance_reference = GetDistance();
  angle_reference = GetAngle();

  initial_rotational_speed = (Robot::m_drivetrain.GetCurvedSpeed(left_velocity) - Robot::m_drivetrain.GetCurvedSpeed(right_velocity)) * ((drivetrain_max_speed * drivetrain_driftiness) / (2 * drivetrain_radius)) / angle;
  if (abs(initial_rotational_speed) < 0.1) {
    initial_rotational_speed = 0;
  }

  initial_velocity = (Robot::m_drivetrain.GetCurvedSpeed(left_velocity) + Robot::m_drivetrain.GetCurvedSpeed(right_velocity)) * drivetrain_max_speed / 2;
  if (abs(initial_velocity) < 2) {
    initial_velocity = 0;
  }

  if (angle == 0 || initial_rotational_speed / angle < 0 || final_rotational_speed / angle < 0 || abs(angle) > 180) {
    goto jumper;
  }
  if ((initial_velocity > 0 && final_velocity < 0) || (initial_velocity < 0 && final_velocity > 0)) {
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
        goto jumper;
      }
      dist = CalcPathX(calc_skew, calc_time) - target_x;
      if (calc_skew < 0 || path_calcs > 379) {
        goto jumper;
      }
    } while (abs(dist) > tolerance);

    stable_skew = calc_skew;
    stable_time = calc_time;
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
    jumper:
      return false;
  }
}

bool DriveTrain::CalculatePath(double x_target, double z_target, double angle, double final_velocity, double final_rotational_speed) {
  dist = sqrt(pow(x_target - x_position, 2) + pow(z_target - z_position, 2));
  return CalculateRawPath(dist * sin(Robot::m_macro_superstructure.GetDirection(x_target - x_position, z_target - z_position) - GetAngle() * pi / 180), dist * cos(Robot::m_macro_superstructure.GetDirection(x_target - x_position, z_target - z_position) - GetAngle() * pi / 180), angle - GetAngle(), final_velocity, final_rotational_speed);
}

void DriveTrain::FollowPath(double time, double time_difference) {
  if (time < stable_i1) {
    left_velocity = ((stable_v1 - stable_c1 * time) + c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
    right_velocity = ((stable_v1 - stable_c1 * time) - c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
    distance = time * (stable_v1 - (stable_c1 * time) / 2);
    direction = (180 / pi) * time * (stable_r1 + (time / (2 * stable_c3)));
  } else if (time < stable_skew) {
    left_velocity = 1;
    right_velocity = 1 - (2 * c[0] * (stable_r1 + (time / stable_c3))) / drivetrain_max_speed;
    distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((time - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - c[0] * (stable_r1 + (time / stable_c3)));
    direction = (180 / pi) * time * (stable_r1 + (time / (2 * stable_c3)));
  } else if (time < stable_i2) {
    left_velocity = 1;
    right_velocity = 1 - (2 * c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
    distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((stable_skew - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - (c[0] * stable_h)) + ((time - stable_skew) / 2) * ((2 * drivetrain_max_speed) + c[0] * (stable_c2 * (time - stable_time) - stable_r2 - stable_h));
    direction = (180 / pi) * (stable_a - (stable_time - time) * ((stable_time - time) * (stable_c2 / 2) + stable_r2));
  } else {
    left_velocity = ((stable_v1 - stable_c1 * time) + c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
    right_velocity = ((stable_v1 - stable_c1 * time) - c[0] * (stable_r2 - stable_c2 * (time - stable_time))) / drivetrain_max_speed;
    distance = stable_i1 * (stable_v1 - (stable_c1 * stable_i1) / 2) + ((stable_skew - stable_i1) / 2) * (stable_v1 - (stable_c1 * stable_i1) + drivetrain_max_speed - (c[0] * stable_h)) + ((stable_i2 - stable_skew) / 2) *  ((2 * drivetrain_max_speed) + c[0] * (stable_c2 * (stable_i2 - stable_time) - stable_r2 - stable_h)) + (time - stable_i2) * (stable_v1 - (stable_c1 * (time + stable_i1) / 2));
    direction = (180 / pi) * (stable_a - (stable_time - time) * ((stable_time - time) * (stable_c2 / 2) + stable_r2));
  }

  if (stable_inverted_direction == true) {
    hold = left_velocity;
    left_velocity = right_velocity;
    right_velocity = hold;
    direction = -direction;
  }

  if (stable_inverted_velocity == true) {
    hold = left_velocity;
    left_velocity = -right_velocity;
    right_velocity = -hold;
    distance = -distance;
  }

  distance_PID = GetDistancePID(distance + distance_reference, time_difference);
  gyro_PID =  GetGyroPID(direction + angle_reference, time_difference);

  if (time < stable_time) {
    SetCurvedSpeed(left_velocity + distance_PID + gyro_PID, right_velocity + distance_PID - gyro_PID);
  }
}

double DriveTrain::GetPathTime() {
  return stable_time;
}

void DriveTrain::ResetTime() {
  stable_time = 0;
}