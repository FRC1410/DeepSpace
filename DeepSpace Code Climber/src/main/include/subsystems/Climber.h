/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>

#include "RobotMap.h"

class Climber : public frc::Subsystem {
  private:
    frc::DoubleSolenoid climber_front_solenoid{climber_front_port_start, climber_front_port_end};
    frc::DoubleSolenoid climber_back_solenoid{climber_back_port_start, climber_back_port_end};
    
    WPI_TalonSRX m_left_stilt{climber_left_stilt};
    WPI_TalonSRX m_right_stilt{climber_right_stilt};
    WPI_TalonSRX m_stilt_mover{climber_stilt_mover};

    bool front_extended;
    bool back_extended;
    
  public:
    Climber();
    void InitDefaultCommand() override;

    void ExtendFront();
    void RetractFront();
    void FrontOff();

    void ExtendBack();
    void RetractBack();
    void BackOff();
    
    bool GetFrontState();
    bool GetBackState();

    void RaiseStilts(double speed);
    void MoveStilts(double speed);
};
