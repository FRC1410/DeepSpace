/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SparkMax.h"
#include "commands/SparkMaxRun.h"

SparkMax::SparkMax() : Subsystem("ExampleSubsystem") {}

void SparkMax::InitDefaultCommand() {
  SetDefaultCommand(new SparkMaxRun());
}

void SparkMax::RunNEO(double speed) {
  m_spark_test.Set(speed);
}

double SparkMax::GetRevolutions() {
  m_encoder.GetPosition();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
