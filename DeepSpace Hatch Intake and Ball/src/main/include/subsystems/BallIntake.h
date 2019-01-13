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
#include "commands/BallIntakeRun.h"

class BallIntake : public frc::Subsystem {
  private:
    WPI_TalonSRX m_ball_intake{Ball_intake};
  public:
    BallIntake();
    void InitDefaultCommand() override;
    void RunIntake(double speed);
};
