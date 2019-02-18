/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

OI Robot::m_oi;
MacroSuperstructure Robot::m_macro_superstructure;
DriveTrain Robot::m_drivetrain;
BallClaw Robot::m_ball_claw;
BallRoller Robot::m_ball_roller;
HatchPickup Robot::m_hatch_pickup;
HatchStick Robot::m_hatch_stick;
Elevator Robot::m_elevator;
Climber Robot::m_climber;
Limelight Robot::m_limelight;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption("Do Nothing", nullptr);
  m_chooser.AddOption("Limelight", &m_auto_limelight_targeting);
  m_chooser.AddOption("Gyro PID", &m_auto_gyro_pid);
  m_chooser.AddOption("Calibrate Elevator", &m_elevator_calibrate);
  m_chooser.AddOption("Stress Test", &m_stress_test);
  m_chooser.AddOption("Calibrate Drivetrain", &m_drivetrain_calibrate);
  frc::SmartDashboard::PutData("Auto", &m_chooser);

  frc::SmartDashboard::PutNumber("Elevator Height", elevator_min_height);

  Robot::m_elevator.ResetEncoders();
  Robot::m_elevator.ResetIntegral();

  m_watchdog.Disable();

  Robot::m_climber.RetractFront();
  Robot::m_hatch_stick.RetractStick();
  Robot::m_ball_roller.RollerUp();
  Robot::m_hatch_pickup.SetState(true);

  Robot::m_drivetrain.DisableSafety();
  Robot::m_hatch_pickup.DisableSafety();
  Robot::m_ball_claw.DisableSafety();
  Robot::m_ball_roller.DisableSafety();
  Robot::m_limelight.SetPipeline(0);
}

/*
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  Robot::m_oi.SetDriverRumbleLeft(0);
  Robot::m_oi.SetDriverRumbleRight(0);
  Robot::m_oi.SetOperatorRumbleLeft(0);
  Robot::m_oi.SetOperatorRumbleRight(0);
}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  std::string auto_selected = frc::SmartDashboard::GetString("Auto", "Default");
  if (auto_selected == "Limelight") {
    m_autonomous_command = &m_auto_limelight_targeting;
  } else if (auto_selected == "Gyro PID") {
    m_autonomous_command = &m_auto_gyro_pid;
  } else if (auto_selected == "Calibrate Elevator") {
    m_autonomous_command = &m_elevator_calibrate;
  } else if (auto_selected == "Stress Test") {
    m_autonomous_command = &m_stress_test;
  } else if (auto_selected == "Calibrate Drivetrain") {
    m_autonomous_command = &m_drivetrain_calibrate;
  } else {
    m_autonomous_command = nullptr;
  }

  m_autonomous_command = m_chooser.GetSelected();
  Robot::m_elevator.ResetEncoders();
  Robot::m_hatch_pickup.ResetEncoder();

  if (m_autonomous_command != nullptr) {
    Robot::m_macro_superstructure.SetAuto(true);
    m_autonomous_command->Start();
  } else {
    Robot::m_macro_superstructure.SetAuto(false);
  }

  Robot::m_limelight.SetPipeline(0);
}

void Robot::AutonomousPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomous_command != nullptr) {
    m_autonomous_command->Cancel();
    m_autonomous_command = nullptr;
  }
  
  Robot::m_limelight.SetPipeline(0);
}

void Robot::TeleopPeriodic() {
  Robot::m_macro_superstructure.SetAuto(false);
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif