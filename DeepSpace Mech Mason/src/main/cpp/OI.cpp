/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/WPILib.h>
#include <frc/GenericHID.h>

#include "OI.h"

OI::OI() {}

double OI::ApplyDeadzone(int controller, int axis, double axis_value, double deadzone) {
  if (axis == 1 || axis == 5) {
    raw_magnitude = sqrt(pow(frc::Joystick{controller}.GetRawAxis(axis), 2) + pow(frc::Joystick{controller}.GetRawAxis(axis - 1), 2));
    if (raw_magnitude <= deadzone) {
      return 0;
    } else {
      return ((raw_magnitude - deadzone)/(1 - deadzone)) * (axis_value/raw_magnitude);
    }
  } else if (axis == 0 || axis == 4) {
    raw_magnitude = sqrt(pow(frc::Joystick{controller}.GetRawAxis(axis), 2) + pow(frc::Joystick{controller}.GetRawAxis(axis + 1), 2));
    if (raw_magnitude <= deadzone) {
      return 0;
    } else {
      return ((raw_magnitude - deadzone)/(1 - deadzone)) * (axis_value/raw_magnitude);
    }
  } else {
    if (axis_value <= deadzone) {
      return 0;
    } else {
      return (axis_value - deadzone)/(1 - deadzone);
    }
  }
}

double OI::GetDriverAxis(int axis, double deadzone) {
  return ApplyDeadzone(driver_port, axis, driver_controller.GetRawAxis(axis), deadzone);
}

bool OI::GetDriverButton(int button) {
  return driver_controller.GetRawButton(button);
}

int OI::GetDriverDPad() {
  return driver_controller.GetPOV();
}

double OI::GetOperatorAxis(int axis, double deadzone) {
  return ApplyDeadzone(operator_port, axis, operator_controller.GetRawAxis(axis), deadzone);
}

bool OI::GetOperatorButton(int button) {
  return operator_controller.GetRawButton(button);
}

int OI::GetOperatorDPad() {
  return operator_controller.GetPOV();
}

void OI::SetDriverRumbleLeft(double value) {
  driver_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
}

void OI::SetDriverRumbleRight(double value) {
  driver_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
}

void OI::SetOperatorRumbleLeft(double value) {
  operator_controller.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, value);
}

void OI::SetOperatorRumbleRight(double value) {
  operator_controller.SetRumble(frc::GenericHID::RumbleType::kRightRumble, value);
}