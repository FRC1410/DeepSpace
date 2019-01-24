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
