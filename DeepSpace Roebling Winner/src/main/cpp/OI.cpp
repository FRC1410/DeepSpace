/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

OI::OI() {}

double OI::ApplyDeadzone(int controller, int axis, double axis_value, double deadzone) {
  if (axis == 1 || axis == 5) {
    raw_magnitude = sqrt(pow(frc::Joystick{controller}.GetRawAxis(axis), 2) + pow(frc::Joystick{controller}.GetRawAxis(axis - 1), 2));
    if (raw_magnitude <= deadzone) {
      return 0;
    } else {
      return ((raw_magnitude - deadzone) / (1 - deadzone)) * (axis_value / raw_magnitude);
    }
  } else if (axis == 0 || axis == 4) {
    raw_magnitude = sqrt(pow(frc::Joystick{controller}.GetRawAxis(axis), 2) + pow(frc::Joystick{controller}.GetRawAxis(axis + 1), 2));
    if (raw_magnitude <= deadzone) {
      return 0;
    } else {
      return ((raw_magnitude - deadzone) / (1 - deadzone)) * (axis_value / raw_magnitude);
    }
  } else {
    return axis_value;
  }
}

double OI::GetDriverAxis(int axis) {
  return ApplyDeadzone(driver_port, axis, driver_controller.GetRawAxis(axis), driver_deadzone);
}

double OI::GetAverageDriverInput() {
  return (GetDriverAxis(drivetrain_left_axis) + GetDriverAxis(drivetrain_right_axis)) / 2;
}

bool OI::GetDriverButton(int button) {
  return driver_controller.GetRawButton(button);
}

void::OI::SetDriverRumble(double left, double right) {
  driver_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, left);
  driver_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, right);
}

int OI::GetDriverDPad() {
  return driver_controller.GetPOV();
}

double OI::GetOperatorAxis(int axis) {
  return ApplyDeadzone(operator_port, axis, operator_controller.GetRawAxis(axis), operator_deadzone);
}

bool OI::GetOperatorButton(int button) {
  return operator_controller.GetRawButton(button);
}

int OI::GetOperatorDPad() {
  return operator_controller.GetPOV();
}

void OI::SetOperatorRumble(double left, double right) {
  operator_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, left);
  operator_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, right);
}

double OI::GetHumanPlayerAxis(int axis) {
  return human_player_controller.GetRawAxis(axis);
}

bool OI::GetHumanPlayerButton(int button) {
  return human_player_controller.GetRawButton(button);
}