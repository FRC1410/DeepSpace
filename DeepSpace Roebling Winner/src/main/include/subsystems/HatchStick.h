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

class HatchStick : public frc::Subsystem {
  private:
    WPI_TalonSRX m_wheels{hatch_stick_wheels};
    frc::DoubleSolenoid stick_solenoid {hatch_stick_port_start, hatch_stick_port_end};
    
    bool extended;
    
    nt::NetworkTableEntry shuffleboard_stick = frc::Shuffleboard::GetTab("Mechanisms").Add("Hatch Stick", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).WithPosition(0, 0).WithSize(1, 1).GetEntry();
    nt::NetworkTableEntry shuffleboard_flex_power = frc::Shuffleboard::GetTab("Mechanisms").Add("Hatch Flex Power", 0).WithWidget(frc::BuiltInWidgets::kDial).WithPosition(0, 1).WithSize(1, 1).GetEntry();

  public:
    HatchStick();
    void InitDefaultCommand() override;

    void RunWheels(double speed);

    void ExtendStick();
    void RetractStick();
    bool GetState();
};