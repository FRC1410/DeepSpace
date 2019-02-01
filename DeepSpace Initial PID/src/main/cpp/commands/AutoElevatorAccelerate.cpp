#include "commands/AutoElevatorAccelerate.h"
#include "Robot.h"

AutoElevatorAccelerate::AutoElevatorAccelerate() {}

// Called just before this Command runs the first time
void AutoElevatorAccelerate::Initialize() {
  timer.Start();
  timer.Reset();
  previous_timer = -0.02;
  acceleration = true;
  max_speed = 0;
  Robot::m_elevator.ResetHeight();
  previous_height = Robot::m_elevator.GetHeight();
}

// Called repeatedly when this Command is scheduled to run
void AutoElevatorAccelerate::Execute() {
  frc::SmartDashboard::PutNumber("Elevator Speed ", (Robot::m_elevator.GetHeight() - previous_height) / (timer.Get() - previous_timer));

  if (acceleration == true) {
    if (abs(max_speed) < abs((Robot::m_elevator.GetHeight() - previous_height) / (timer.Get() - previous_timer))) {
      max_speed = (Robot::m_elevator.GetHeight() - previous_height) / (timer.Get() - previous_timer);
      deceleration_distance = abs(max_speed) * max_speed / 772.18;
    }
  }

  if (desired_height - Robot::m_elevator.GetHeight() < deceleration_distance) {
    acceleration = false;
    Robot::m_elevator.RunElevator(final_inputted_velocity * sqrt((desired_height - Robot::m_elevator.GetHeight()) / deceleration_distance) + elevator_weak_gravity);
  } else {
    final_inputted_velocity = elevator_strong_gravity + ((timer.Get() + 0.02) / (elevator_accleration_time + 0.02)) * (1 - elevator_strong_gravity);
    if (abs(final_inputted_velocity) < 1) {
      Robot::m_elevator.RunElevator(final_inputted_velocity);
    } else {
      Robot::m_elevator.RunElevator(abs(final_inputted_velocity)/final_inputted_velocity); 
    }
  }

  previous_height = Robot::m_elevator.GetHeight();
  previous_timer = timer.Get();
  frc::SmartDashboard::PutNumber("Elevator Height", previous_height);
  frc::SmartDashboard::PutNumber("Auto Timer", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool AutoElevatorAccelerate::IsFinished() { 
  if (Robot::m_macro_superstructure.GetAuto() == false || abs(desired_height - Robot::m_elevator.GetHeight()  ) < 1) {
    return true;
  } else {
    return false;
  }
}

// Called once after isFinished returns true
void AutoElevatorAccelerate::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoElevatorAccelerate::Interrupted() {}
