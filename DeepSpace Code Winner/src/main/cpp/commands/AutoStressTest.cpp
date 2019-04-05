/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoStressTest.h"
#include "Robot.h"

AutoStressTest::AutoStressTest() {}

// Called just before this Command runs the first time
void AutoStressTest::Initialize() {
  frc::SmartDashboard::PutNumber("Calculations per tick", 1000);
  integral = 0;
  x = 1;

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
}

// Called repeatedly when this Command is scheduled to run
void AutoStressTest::Execute() {
  calcs = frc::SmartDashboard::GetNumber("Calculations per tick", 1000);

  while (x % calcs > 0) {
    integral += sin(pow(double(x) / 5000000, 2)) / 5000000;
    x++;
  }

  integral += sin(pow(double(x) / 5000000, 2)) / 5000000;
  x++;
  
  frc::SmartDashboard::PutNumber("Time Difference", m_timer.Get() - previous_timer);
  previous_timer = m_timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoStressTest::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoStressTest::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoStressTest::Interrupted() {}
