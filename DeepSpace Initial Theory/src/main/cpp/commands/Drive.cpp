#include "commands/Drive.h"
#include "Robot.h"

Drive::Drive() {
	Requires(&Robot::m_drivetrain);
  Requires(&Robot::m_limelight);
}

// Called just before this Command runs the first time
void Drive::Initialize() {
  Robot::m_drivetrain.ResetNavX();
  timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
	  if (start_was_pressed == false) {
      timer.Reset();
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

  frc::SmartDashboard::PutNumber("NavX Value", Robot::m_drivetrain.GetAngle());

  frc::SmartDashboard::PutNumber("Left Tape Sensor", Robot::m_drivetrain.GetLeftSensor());
  frc::SmartDashboard::PutNumber("Middle Tape Sensor", Robot::m_drivetrain.GetMiddleSensor());
  frc::SmartDashboard::PutNumber("Right Tape Sensor", Robot::m_drivetrain.GetRightSensor());

  /*if (Robot::m_drivetrain.GetMiddleSensor() == true) {
    Robot::m_oi.SetDriverRumbleLeft(0.3);
    Robot::m_oi.SetDriverRumbleRight(0.3);
  } else {
    Robot::m_oi.SetDriverRumbleLeft(0);
    Robot::m_oi.SetDriverRumbleRight(0);
  }*/

  if (invert_driving == false) {
  	Robot::m_drivetrain.TankDrive(left_stick_amount, right_stick_amount);
    if (timer.Get() < 0.2) {
      Robot::m_oi.SetDriverRumbleLeft(0.5);
      Robot::m_oi.SetDriverRumbleRight(0.5);
    } else {
      Robot::m_oi.SetDriverRumbleLeft(0);
      Robot::m_oi.SetDriverRumbleRight(0);
    }
  } else {
  	Robot::m_drivetrain.TankDrive(-right_stick_amount, -left_stick_amount);
    if (timer.Get() < 0.1) {
      Robot::m_oi.SetDriverRumbleLeft(1);
      Robot::m_oi.SetDriverRumbleRight(1);
    } else if (timer.Get() > 0.25 && timer.Get() < 0.3) {
      Robot::m_oi.SetDriverRumbleLeft(1);
      Robot::m_oi.SetDriverRumbleRight(1);
    } else {
      Robot::m_oi.SetDriverRumbleLeft(0);
      Robot::m_oi.SetDriverRumbleRight(0);
    }
  }
  
  if (Robot::m_oi.GetOperatorButton(6) == true) {
    if (fmod(timer.Get(), 0.4) < 0.2) {
      Robot::m_oi.SetOperatorRumbleLeft(1);
      Robot::m_oi.SetOperatorRumbleRight(0);
    } else {
      Robot::m_oi.SetOperatorRumbleLeft(0);
      Robot::m_oi.SetOperatorRumbleRight(1);
    }
  } else {
    Robot::m_oi.SetOperatorRumbleLeft(0);
    Robot::m_oi.SetOperatorRumbleRight(0);
  }

  frc::SmartDashboard::PutNumber("Target Found", Robot::m_limelight.GetTarget());
  frc::SmartDashboard::PutNumber("Target X", Robot::m_limelight.GetTargetX());
  frc::SmartDashboard::PutNumber("Target Y", Robot::m_limelight.GetTargetY());
  frc::SmartDashboard::PutNumber("Target Area", Robot::m_limelight.GetTargetArea());
  frc::SmartDashboard::PutNumber("Target Skewness", Robot::m_limelight.GetTargetSkew());
  frc::SmartDashboard::PutNumber("Latency", Robot::m_limelight.GetCameraLatency());

  if (Robot::m_oi.GetOperatorButton(1)) {
    Robot::m_limelight.TurnOffLights();
  } else {
    Robot::m_limelight.TurnOnLights();
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
