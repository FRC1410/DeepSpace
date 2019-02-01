#include "commands/AutoBetterLineSensor.h"
#include "Robot.h"

AutoBetterLineSensor::AutoBetterLineSensor() {}

// Called just before this Command runs the first time
void AutoBetterLineSensor::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoBetterLineSensor::Execute() {
  if ((Robot::m_drivetrain.GetMiddleSensor() == false) && (Robot::m_drivetrain.GetLeftSensor() == false) && (Robot::m_drivetrain.GetRightSensor() == false)) {
    Robot::m_drivetrain.TankDrive(0.5, 0.5);
  } else if(Robot::m_drivetrain.GetLeftSensor() == true) {
    Robot::m_drivetrain.TankDrive(0.3, 0.5);
  } else if(Robot::m_drivetrain.GetRightSensor() == true) {
    Robot::m_drivetrain.TankDrive(0.5, 0.3);
  } else if(Robot::m_drivetrain.GetMiddleSensor() == true) {
    Robot::m_drivetrain.TankDrive(0.5, 0.5);
  }
}

// Make this return true when this Command no longer needs to run execute()
bool AutoBetterLineSensor::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoBetterLineSensor::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoBetterLineSensor::Interrupted() {}
