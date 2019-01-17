/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include "RobotMap.h"

class SparkMax : public frc::Subsystem {
  private:
    rev::CANSparkMax m_spark_test{spark_max_test, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANEncoder m_encoder = m_spark_test.GetEncoder();

  public:
    SparkMax();
    void InitDefaultCommand() override;
    void RunNEO(double speed);
    double GetRevolutions();
};
