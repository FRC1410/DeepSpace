#include "commands/ElevatorRun.h"
#include "Robot.h"

ElevatorRun::ElevatorRun() {
  Requires(&Robot::m_elevator);
}

// Called just before this Command runs the first time
void ElevatorRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {
  operator_left_stick_input = -Robot::m_oi.GetOperatorAxis(1, default_operator_deadzone);
  Robot::m_elevator.RunElevator(operator_left_stick_input);

  frc::SmartDashboard::PutNumber("Elevator Left Revolutions", Robot::m_elevator.GetLeftRevolutions());
  frc::SmartDashboard::PutNumber("Elevator Right Revolutions", Robot::m_elevator.GetRightRevolutions());
  frc::SmartDashboard::PutNumber("Operator Left Stick", operator_left_stick_input);
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
