#include "commands/AutoLineSensor.h"
#include "Robot.h"

AutoLineSensor::AutoLineSensor() {}

// Called just before this Command runs the first time
void AutoLineSensor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoLineSensor::Execute() {
  if (Robot::m_drivetrain.GetMiddleSensor() == true) {
    if (Robot::m_drivetrain.GetLeftSensor() == true) {
      if (Robot::m_drivetrain.GetRightSensor() == true) {
        Robot::m_drivetrain.TankDrive(0.5, 0.5);
      } else {
        Robot::m_drivetrain.TankDrive(0.4, 0.5);
      }
    } else if (Robot::m_drivetrain.GetRightSensor() == true) {
      Robot::m_drivetrain.TankDrive(0.5, 0.4);
    } else {
      Robot::m_drivetrain.TankDrive(0.5, 0.5);
    }
  } else if (Robot::m_drivetrain.GetLeftSensor() == true) {
    if (Robot::m_drivetrain.GetRightSensor() == true) {
      Robot::m_drivetrain.TankDrive(0.5, 0.5);
    } else {
      Robot::m_drivetrain.TankDrive(0.3, 0.5);
    }
  } else if (Robot::m_drivetrain.GetRightSensor() == true) {
    Robot::m_drivetrain.TankDrive(0.5, 0.3);
  } else {
    Robot::m_drivetrain.TankDrive(0, 0);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoLineSensor::IsFinished() { 
  return false;
}

// Called once after isFinished returns true
void AutoLineSensor::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoLineSensor::Interrupted() {}