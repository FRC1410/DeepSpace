/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>

#include "RobotMap.h"

class HatchStick : public frc::Subsystem {
  private:
    frc::DoubleSolenoid stick_solenoid {hatch_stick_port_start, hatch_stick_port_end};
    bool extended;

  public:
    HatchStick();
    void InitDefaultCommand() override;
    void ExtendStick();
    void RetractStick();
    void StickOff();
    bool GetState();
};