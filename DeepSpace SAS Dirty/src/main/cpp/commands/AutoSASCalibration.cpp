/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoSASCalibration.h"
#include "Robot.h"

AutoSASCalibration::AutoSASCalibration() {
  x_position = -47;
  y_position = 67;
  previous_angle = Robot::m_drivetrain.GetAngle();
}

// Called just before this Command runs the first time
void AutoSASCalibration::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoSASCalibration::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool AutoSASCalibration::IsFinished() {
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false;
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoSASCalibration::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoSASCalibration::Interrupted() {}
