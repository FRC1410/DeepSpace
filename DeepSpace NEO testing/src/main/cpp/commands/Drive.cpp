#include "commands/Drive.h"
#include "Robot.h"
#include "RobotMap.h"
#include "OI.h"

Drive::Drive() {
	Requires(&Robot::m_drivetrain);
}

// Called just before this Command runs the first time
void Drive::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
	  if (start_was_pressed == false) {
	    if (invert_driving == false) {
	      invert_driving = true;
	      frc::SmartDashboard::PutString("Inverted Driving", "Yes");
      } else {
	      invert_driving = false;
	      frc::SmartDashboard::PutString("Inverted Driving", "No");
	    }
    }
	  start_was_pressed = true;
  } else {
	  start_was_pressed = false;
  }

  left_stick_amount = -Robot::m_oi.GetDriverAxis(1, default_driver_deadzone);
  right_stick_amount = -Robot::m_oi.GetDriverAxis(5, default_driver_deadzone);

  frc::SmartDashboard::PutNumber("Left Stick Value", left_stick_amount);
  frc::SmartDashboard::PutNumber("Right Stick Value", right_stick_amount);

  if (invert_driving == false) {
  	Robot::m_drivetrain.TankDrive(left_stick_amount, right_stick_amount);
  } else {
  	Robot::m_drivetrain.TankDrive(-right_stick_amount, -left_stick_amount);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void Drive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {}
