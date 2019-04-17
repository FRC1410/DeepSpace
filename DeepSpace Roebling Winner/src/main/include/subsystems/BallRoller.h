/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class BallRoller : public frc::Subsystem {
  private:
    WPI_TalonSRX m_ball_roller{ball_roller};
    frc::DoubleSolenoid ball_solenoid{ball_roller_rotator_port_start, ball_roller_rotator_port_end};
    
    bool extended;

    nt::NetworkTableEntry shuffleboard_roller = frc::Shuffleboard::GetTab("Mechanisms").Add("Ball Roller", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(6, 1).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_power = frc::Shuffleboard::GetTab("Mechanisms").Add("Roller Power", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(6, 2).WithSize(1, 1).GetEntry();
    
  public:
    BallRoller();
    void InitDefaultCommand() override;

    void RunIntake(double speed);
    void RollerDown();
    void RollerUp();
    bool GetState();
};