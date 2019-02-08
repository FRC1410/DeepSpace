#include "commands/AutoBetterLineSensor.h"
#include "Robot.h"

AutoBetterLineSensor::AutoBetterLineSensor() {}

// Called just before this Command runs the first time
void AutoBetterLineSensor::Initialize() {
  timer.Start();
  timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void AutoBetterLineSensor::Execute() {
  if (Robot::m_drivetrain.GetMiddleSensor() == false && Robot::m_drivetrain.GetLeftSensor() == false && Robot::m_drivetrain.GetRightSensor() == false) {
    if (timer.Get() < 0.3) {
      Robot::m_drivetrain.SetSpeed(-0.1, -0.3);
    } else if (timer.Get() < 0.6) {
      Robot::m_drivetrain.SetSpeed(-0.3, -0.1);
    } else {
      timer.Reset();
    }
  } else if (Robot::m_drivetrain.GetLeftSensor() == true) {
    Robot::m_drivetrain.SetSpeed(-0.5, -0.4);
    if (Robot::m_drivetrain.GetLeftSensor() == false && timer.Get() > 0.01) {
      Robot::m_drivetrain.SetSpeed(0.5, 0.4);
      if(Robot::m_drivetrain.GetLeftSensor() == true) {
        Robot::m_drivetrain.SetSpeed(-0.2, -0.5);
      }
    }
  } else if (Robot::m_drivetrain.GetRightSensor() == true) {
    Robot::m_drivetrain.SetSpeed(-0.4, -0.5);
    if(Robot::m_drivetrain.GetRightSensor() == false) {
      Robot::m_drivetrain.SetSpeed(0.4, 0.5);
      if (Robot::m_drivetrain.GetRightSensor() == true) {
        Robot::m_drivetrain.SetSpeed(-0.5, -0.2);
      }
    }
  } else if (Robot::m_drivetrain.GetMiddleSensor() == true && Robot::m_drivetrain.GetLeftSensor() == false && Robot::m_drivetrain.GetRightSensor() == false) {
    Robot::m_drivetrain.SetSpeed(0, 0);
  }
} 

// Make this return true when this Command no longer needs to run execute()
bool AutoBetterLineSensor::IsFinished() { 
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    return false; 
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoBetterLineSensor::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoBetterLineSensor::Interrupted() {}
