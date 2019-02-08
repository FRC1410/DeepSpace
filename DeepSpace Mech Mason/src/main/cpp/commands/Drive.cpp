#include "commands/Drive.h"
#include "Robot.h"

Drive::Drive() {
	Requires(&Robot::m_drivetrain);
}

// Called just before this Command runs the first time
void Drive::Initialize() {
  Robot::m_drivetrain.ResetNavX();
  rumble_timer.Start();
  timer.Start();
  previous_timer = -0.02;

  x_position = 0;
  y_position = 0;

  previous_left_speed = 0;
  previous_right_speed = 0;
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
  if (Robot::m_macro_superstructure.GetAuto() == false) {
    if (Robot::m_oi.GetDriverButton(invert_driving_button) == true) {
  	  if (invert_button_was_pressed == false) {
        rumble_timer.Reset();
  	    if (invert_driving == false) {
  	      invert_driving = true;
  	      frc::SmartDashboard::PutString("Inverted Driving", "Yes");
        } else {
  	      invert_driving = false;
  	      frc::SmartDashboard::PutString("Inverted Driving", "No");
  	    }
      }
  	  invert_button_was_pressed = true;
    } else {
  	  invert_button_was_pressed = false;
    }

    left_stick_amount = -Robot::m_oi.GetDriverAxis(1, driver_deadzone);
    right_stick_amount = -Robot::m_oi.GetDriverAxis(5, driver_deadzone);

    frc::SmartDashboard::PutNumber("Left Stick Value", left_stick_amount);
    frc::SmartDashboard::PutNumber("Right Stick Value", right_stick_amount);

    frc::SmartDashboard::PutNumber("NavX Value", Robot::m_drivetrain.GetAngle());

    frc::SmartDashboard::PutNumber("Left Tape Sensor", Robot::m_drivetrain.GetLeftSensor());
    frc::SmartDashboard::PutNumber("Middle Tape Sensor", Robot::m_drivetrain.GetMiddleSensor());
    frc::SmartDashboard::PutNumber("Right Tape Sensor", Robot::m_drivetrain.GetRightSensor());

    if (Robot::m_drivetrain.GetMiddleSensor() == true) {
      Robot::m_oi.SetDriverRumbleLeft(0.3);
      Robot::m_oi.SetDriverRumbleRight(0.3);
    } else {
      Robot::m_oi.SetDriverRumbleLeft(0);
      Robot::m_oi.SetDriverRumbleRight(0);
    }

    if (invert_driving == false) {
    	Robot::m_drivetrain.SetSpeed(left_stick_amount, right_stick_amount);
      if (rumble_timer.Get() < 0.25) {
        Robot::m_oi.SetDriverRumbleLeft(1);
        Robot::m_oi.SetDriverRumbleRight(1);
      } else {
        Robot::m_oi.SetDriverRumbleLeft(0);
        Robot::m_oi.SetDriverRumbleRight(0);
      }
    } else {
    	Robot::m_drivetrain.SetSpeed(-right_stick_amount, -left_stick_amount);
      if (rumble_timer.Get() < 0.15 || (rumble_timer.Get() > 0.3 && rumble_timer.Get() < 0.45)) {
        Robot::m_oi.SetDriverRumbleLeft(1);
        Robot::m_oi.SetDriverRumbleRight(1);
      } else {
        Robot::m_oi.SetDriverRumbleLeft(0);
        Robot::m_oi.SetDriverRumbleRight(0);
      }
    }
  }

  x_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * sin(Robot::m_drivetrain.GetAngle() * pi / 180) * (timer.Get() - previous_timer);
  y_position += (Robot::m_drivetrain.GetDistance() - previous_distance) * cos(Robot::m_drivetrain.GetAngle() * pi / 180) * (timer.Get() - previous_timer);

  frc::SmartDashboard::PutNumber("X Position", x_position);
  frc::SmartDashboard::PutNumber("Y Position", y_position);
  frc::SmartDashboard::PutNumber("Target Found", Robot::m_limelight.GetTarget());
  frc::SmartDashboard::PutNumber("Target X", Robot::m_limelight.GetTargetX());
  frc::SmartDashboard::PutNumber("Target Y", Robot::m_limelight.GetTargetY());
  frc::SmartDashboard::PutNumber("Target Area", Robot::m_limelight.GetTargetArea());
  frc::SmartDashboard::PutNumber("Target Skewness", Robot::m_limelight.GetTargetSkew());
  frc::SmartDashboard::PutNumber("Latency", Robot::m_limelight.GetCameraLatency());
  frc::SmartDashboard::PutBoolean("Auto Running", Robot::m_macro_superstructure.GetAuto());

  previous_timer = timer.Get();
  previous_distance = Robot::m_drivetrain.GetDistance();
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