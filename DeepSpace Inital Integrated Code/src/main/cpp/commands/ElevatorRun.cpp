#include "commands/ElevatorRun.h"
#include "Robot.h"

ElevatorRun::ElevatorRun() {
  Requires(&Robot::m_elevator);
}

// Called just before this Command runs the first time
void ElevatorRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {
  elevator_input = -Robot::m_oi.GetOperatorAxis(elevator_axis, default_operator_deadzone);
  if (abs(elevator_input) > 0) {
    Robot::m_elevator.RunElevator(elevator_input);
  }

  frc::SmartDashboard::PutNumber("Elevator Left Revolutions", Robot::m_elevator.GetLeftRevolutions());
  frc::SmartDashboard::PutNumber("Elevator Right Revolutions", Robot::m_elevator.GetRightRevolutions());
  frc::SmartDashboard::PutNumber("Elevator Input", elevator_input);

  frc::SmartDashboard::PutNumber("Left NEO Temperature", Robot::m_elevator.GetLeftTemperature());
  frc::SmartDashboard::PutNumber("Right NEO Temperature", Robot::m_elevator.GetRightTemperature());
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void ElevatorRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRun::Interrupted() {}