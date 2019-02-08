/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>
#include <wpi/raw_ostream.h>

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
  m_chooser.SetDefaultOption("Line Sensor", &m_auto_line_sensor);
  m_chooser.AddOption("Limelight", &m_auto_limelight_targeting);
  m_chooser.AddOption("Gyro PID", &m_auto_gyro_pid);
  frc::SmartDashboard::PutData("Auto", &m_chooser);
  Robot::m_limelight.TurnOffLights();
  frc::CameraServer::GetInstance()->StartAutomaticCapture();
  frc::SmartDashboard::PutNumber("Elevator Height", elevator_min_height);
  Robot::m_elevator.ResetEncoders();
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
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
  Robot::m_oi.SetDriverRumbleLeft(0);
  Robot::m_oi.SetDriverRumbleRight(0);
  Robot::m_limelight.TurnOffLights();
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
  } else {
    m_autonomous_command = &m_auto_line_sensor;
  }

  m_autonomous_command = m_chooser.GetSelected();
  Robot::m_elevator.ResetEncoders();

  if (m_autonomous_command != nullptr) {
    m_autonomous_command->Start();
  }
}

void Robot::AutonomousPeriodic() { 
  Robot::m_macro_superstructure.SetAuto(true);
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
  Robot::m_drivetrain.SetSpeed(0, 0);
  Robot::m_elevator.ResetEncoders();
  Robot::m_macro_superstructure.StartCompressor();
}

void Robot::TeleopPeriodic() {
  Robot::m_macro_superstructure.SetAuto(false);
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif