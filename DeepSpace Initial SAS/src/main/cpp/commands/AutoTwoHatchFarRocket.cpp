/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AutoTwoHatchFarRocket.h"
#include "Robot.h"

AutoTwoHatchFarRocket::AutoTwoHatchFarRocket() {}

// Called just before this Command runs the first time
void AutoTwoHatchFarRocket::Initialize() {
  stage = 0;

  m_timer.Reset();
  m_timer.Start();

  previous_timer = -0.02;
  path_timer = 0;

  Robot::m_drivetrain.CalculatePath(-32, 116, -25, 150, 0);
}

// Called repeatedly when this Command is scheduled to run
void AutoTwoHatchFarRocket::Execute() {
  switch (stage) {
    case 0:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-79, 183, -25, 150, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        path_timer = Robot::m_drivetrain.GetPathTime();
        Robot::m_drivetrain.CalculateRawPath(21.3508, 119.139, 53.75, 0, 0);
        stage = 1;
      }
      break;
    case 1:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-110, 300, 28.75, 0, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        stage = 2;
      }
      break;
    case 2:
      if (m_timer.Get() - path_timer < Robot::m_drivetrain.GetPathTime()) {
        if (Robot::m_drivetrain.CalculatePath(-110, 300, 28.75, 0, 0) == true)  {
          path_timer = previous_timer;
        }
        Robot::m_drivetrain.FollowPath(m_timer.Get() - path_timer, m_timer.Get() - previous_timer);
      } else {
        stage = 3;
      }
      Robot::m_elevator.Goto(elevator_mid_hatch_height, m_timer.Get() - previous_timer);
      break;
    case 3:
      if (stage)
    default:
      Robot::m_drivetrain.SetSpeed(0, 0);
  }
  
  previous_timer = m_timer.Get();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTwoHatchFarRocket::IsFinished() { return false; }

// Called once after isFinished returns true
void AutoTwoHatchFarRocket::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTwoHatchFarRocket::Interrupted() {}
