#include "commands/BallRollerRun.h"
#include "Robot.h"

BallRollerRun::BallRollerRun() {
  Requires(&Robot::m_ball_roller);
}

// Called just before this Command runs the first time
void BallRollerRun::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BallRollerRun::Execute() {
  if (Robot::m_macro_superstructure.GetReset() == false) {
    if (Robot::m_macro_superstructure.GetProfile() == ball_profile_number) {
      if (Robot::m_elevator.GetAverageRevolutions() <= 20 && Robot::m_ball_claw.GetLimitSwitch() == true) {
        Robot::m_ball_roller.RunIntake(Robot::m_oi.GetOperatorAxis(ball_both_intakes_axis, 0) - Robot::m_oi.GetOperatorAxis(ball_both_outtakes_axis, 0));
      }
      if (Robot::m_oi.GetOperatorButton(ball_roller_rotator_button) == true) {
    		if (button_was_pressed == false) {
    			if (roller_extended == false) {
            Robot::m_ball_roller.RollerDown();
            roller_extended = true;
  			  } else {
            Robot::m_ball_roller.RollerUp();
            roller_extended = false;
  			  }
  		  }
  	    button_was_pressed = true;
  	  } else {
  	    button_was_pressed = false;
  	  }
    }
  } else {
    Robot::m_ball_roller.RollerUp();
    roller_extended = false;
  }
  frc::SmartDashboard::PutBoolean("Roller State", roller_extended);
}

// Make this return true when this Command no longer needs to run execute()
bool BallRollerRun::IsFinished() { 
  return false; 
}

// Called once after isFinished returns true
void BallRollerRun::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BallRollerRun::Interrupted() {}