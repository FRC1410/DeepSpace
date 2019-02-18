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
  timer.Start();
  timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void AutoStressTest::Execute() {
  calcs = frc::SmartDashboard::GetNumber("Calculations per tick", 1000);
  frc::SmartDashboard::PutNumber("Calculations", calcs);
  while (x % calcs > 0) {
    integral += sin(pow(double(x) / 5000000, 2)) / 5000000;
    x++;
  }
  integral += sin(pow(double(x) / 5000000, 2)) / 5000000;
  x++;
  frc::SmartDashboard::PutNumber("x", double(x) / 5000000);
  frc::SmartDashboard::PutNumber("Integral", integral);
  frc::SmartDashboard::PutNumber("Time Difference", timer.Get());
  timer.Reset();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoStressTest::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoStressTest::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoStressTest::Interrupted() {}
