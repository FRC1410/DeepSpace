/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/phoenix.h>
#include "RobotMap.h"
#include "commands/HatchWheelsRun.h"

class HatchIntake : public frc::Subsystem {
 private:
  WPI_TalonSRX m_left_wheel{hatch_wheels_left};
  WPI_TalonSRX m_right_wheel{hatch_wheels_right};

 public:
  HatchIntake();
  void InitDefaultCommand() override;
  void RunWheels(double speed);
};
