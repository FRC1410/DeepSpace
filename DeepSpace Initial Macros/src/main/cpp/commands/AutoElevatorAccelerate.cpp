#include "commands/AutoElevatorAccelerate.h"
#include "Robot.h"

AutoElevatorAccelerate::AutoElevatorAccelerate() {}

// Called just before this Command runs the first time
void AutoElevatorAccelerate::Initialize() {
  timer.Start();
  timer.Reset();
  elevator_encoder = Robot::m_elevator.GetAverageRevolutions();
  previous_height = Robot::m_elevator.GetAverageRevolutions();
}

// Called repeatedly when this Command is scheduled to run
void AutoElevatorAccelerate::Execute() {
  if (Robot::m_elevator.GetAverageRevolutions() - elevator_encoder < 15) {
    Robot::m_elevator.RunElevator(timer.Get());
    frc::SmartDashboard::PutNumber("Elevator Speed", timer.Get());
    frc::SmartDashboard::PutNumber("Actual to estimated", (Robot::m_elevator.GetAverageRevolutions() - elevator_encoder - previous_height) * 50 / (timer.Get() - 0.02));
  } else {
    if (previous_height < 15) {
      acceleration_time = timer.Get() - 0.02 + (15 - previous_height)/((Robot::m_elevator.GetAverageRevolutions() - elevator_encoder - previous_height) * 50);
    }
    Robot::m_elevator.RunElevator(2 * acceleration_time - timer.Get());
    frc::SmartDashboard::PutNumber("Elevator Speed", 2 * acceleration_time - timer.Get());
    frc::SmartDashboard::PutNumber("Actual to estimated", (Robot::m_elevator.GetAverageRevolutions() - elevator_encoder - previous_height) * 50 / (2 * acceleration_time - timer.Get() + 0.02));
  }
  frc::SmartDashboard::PutNumber("Actual Speed", (Robot::m_elevator.GetAverageRevolutions() - elevator_encoder - previous_height) * 50);

  previous_height = Robot::m_elevator.GetAverageRevolutions() - elevator_encoder;
  frc::SmartDashboard::PutNumber("Elevator Height", previous_height);
  frc::SmartDashboard::PutNumber("Auto Timer", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool AutoElevatorAccelerate::IsFinished() { 
  if (Robot::m_macro_superstructure.GetAuto() == true) {
    if (previous_height > 15) {
      if (timer.Get() >= 2 * acceleration_time) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return true;
  }
}

// Called once after isFinished returns true
void AutoElevatorAccelerate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoElevatorAccelerate::Interrupted() {}
