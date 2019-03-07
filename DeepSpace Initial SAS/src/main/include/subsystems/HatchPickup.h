/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>

#include "RobotMap.h"

class HatchPickup : public frc::Subsystem {
  private:
    WPI_TalonSRX m_rotator{hatch_pickup_rotator};
    double error, P, D;
    double I = 0;
    double previous_error = 0;
    bool raised = true;
    
  public:
    HatchPickup();
    void InitDefaultCommand() override;
    
    void RotatePickup(double speed);

    void ResetEncoder();
    double GetPosition();

    void SetState(bool state);
    bool GetState();

    double GetPID(double target, double time_difference);
    void ResetIntegral();
};