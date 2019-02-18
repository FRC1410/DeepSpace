/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

#include "RobotMap.h"

class BallClaw : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_wheel{ball_claw_left};
    WPI_TalonSRX m_right_wheel{ball_claw_right};

    DigitalInput * ball_limit_switch = new DigitalInput(claw_limit_switch);

  public:
    BallClaw();
    void InitDefaultCommand() override;
    void DisableSafety();
    void RunWheels(double left, double right);
    bool GetLimitSwitch();
};