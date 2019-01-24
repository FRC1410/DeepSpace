#include "commands/SparkMaxRun.h"
#include "Robot.h"

SparkMaxRun::SparkMaxRun() {
  Requires(&Robot::m_spark_max);
}

// Called just before this Command runs the first time
void SparkMaxRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SparkMaxRun::Execute() {
  stick_input = Robot::m_oi.GetOperatorAxis(1, default_operator_deadzone);
  Robot::m_spark_max.RunNEO(stick_input);

  frc::SmartDashboard::PutNumber("NEO Revolutions", Robot::m_spark_max.GetRevolutions());
  frc::SmartDashboard::PutNumber("Operator Input", stick_input);
}

// Make this return true when this Command no longer needs to run execute()
bool SparkMaxRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void SparkMaxRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SparkMaxRun::Interrupted() {}
