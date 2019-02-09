#include "commands/AutoBetterLineSensor.h"
#include "Robot.h"

AutoBetterLineSensor::AutoBetterLineSensor() {}

// Called just before this Command runs the first time
void AutoBetterLineSensor::Initialize() {
  timer.Start();
  step = 0;
  frc::SmartDashboard::PutBoolean("Auto Failed?", false);
  Robot::m_drivetrain.SetSpeed(-0.1, -0.3);
}

// Called repeatedly when this Command is scheduled to run
void AutoBetterLineSensor::Execute() {
  if (Robot::m_drivetrain.GetMiddleSensor() == false && Robot::m_drivetrain.GetLeftSensor() == false && Robot::m_drivetrain.GetRightSensor() == false) {
    switch (step) {
      case 0:
        timer.Reset();
        if (timer.Get() > 0.5) {
          Robot::m_drivetrain.Accelerate(-0.3, -0.1);
          step = 1;
        }
        break;
      case 1:
        if (timer.Get() > 1) {
          Robot::m_drivetrain.Accelerate(-0.1, -0.3);
          step = 2;
        }
        break;
      case 2:
        if (timer.Get() > 1.5) {
          Robot::m_drivetrain.Accelerate(-0.3, -0.1);
          step = 3;
        }
        break;
      case 3:
        if (timer.Get() > 2) {
          Robot::m_drivetrain.Accelerate(-0.1, -0.3);
          step = 4;
        }
        break;
      case 4:
        if (timer.Get() > 2.5) {
          Robot::m_drivetrain.Accelerate(-0.3, -0.1);
          step = 5;
        }
        break;
      case 5:
        if (timer.Get() > 3) {
          Robot::m_drivetrain.Accelerate(-0.1, -0.3);
          step = 5;
        }
        break;
     case 6:
        if (timer.Get() > 3.5) {
          Robot::m_drivetrain.Accelerate(0, 0);
           frc::SmartDashboard::PutBoolean("Auto Failed?", true);
        }
        break;
    } 
  }
  
  if (Robot::m_drivetrain.GetLeftSensor() == true) {
    Robot::m_drivetrain.Accelerate(-0.5, -0.4);
  } else if (Robot::m_drivetrain.GetRightSensor() == true) {
    Robot::m_drivetrain.Accelerate(-0.4, -0.5);
  } else if (Robot::m_drivetrain.GetMiddleSensor() == true) {
    Robot::m_drivetrain.Accelerate(0, 0);
  }
  
  frc::SmartDashboard::PutNumber("Step", step);
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
