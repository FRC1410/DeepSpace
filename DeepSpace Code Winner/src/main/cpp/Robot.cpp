/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//frc::Shuffleboard::GetTab("Calibration Menu").Add("something", 18).WithWidget("are u stupid").GetEntry();
#include "Robot.h"
#include <frc/commands/Scheduler.h>

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
  Robot::m_ball_roller.RollerUp();
  Robot::m_hatch_stick.RetractStick();
  Robot::m_climber.RetractFront();
  Robot::m_climber.RetractBack();

  m_chooser.SetDefaultOption("Do Nothing", nullptr);
  m_chooser.AddOption("Distance PID", &m_distance_pid);
  m_chooser.AddOption("Gyro PID", &m_gyro_pid);
  m_chooser.AddOption("Rocket Pure PID", &m_hatch_near_rocket);
  m_chooser.AddOption("Rocket AdaptivevPID", &m_rocket_adjustment);
  m_chooser.AddOption("Calibrate Elevator", &m_elevator_calibrate);
  m_chooser.AddOption("Calibrate Drivetrain", &m_drivetrain_calibrate);
  m_chooser.AddOption("Stress Test", &m_stress_test);
  m_chooser.AddOption("Two Hatch Far Rocket", &m_far_rocket);
  frc::SmartDashboard::PutData("Auto", &m_chooser);

  frc::SmartDashboard::PutBoolean("Auto Inverter", false);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
  Robot::m_oi.SetDriverRumbleLeft(0);
  Robot::m_oi.SetDriverRumbleRight(0);
  Robot::m_oi.SetOperatorRumbleLeft(0);
  Robot::m_oi.SetOperatorRumbleRight(0);
  Robot::m_limelight.TurnOffLights();
  Robot::m_limelight.SetPipeline(0);
}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
  m_macro_superstructure.SetInvertedAuto(frc::SmartDashboard::GetBoolean("Auto Inverter", false));

  m_drivetrain.ResetEncoders();
  m_elevator.ResetEncoders();
  m_hatch_pickup.ResetEncoder();
  m_drivetrain.ResetNavX(0);
  
  m_drivetrain.SetX(-47 * Robot::m_macro_superstructure.GetInvertedAuto());
  m_drivetrain.SetZ(67);

  Robot::m_drivetrain.ResetDistanceIntegral();
  Robot::m_drivetrain.ResetGyroIntegral();
  Robot::m_drivetrain.ResetTime();

  m_drivetrain.SetSpeed(0, 0);
  m_elevator.RunElevator(0);

  Robot::m_limelight.TurnOnLights();
  Robot::m_limelight.SetPipeline(2);
  
  m_macro_superstructure.SetHandoffStage(0);

  std::string auto_selected = frc::SmartDashboard::GetString("Auto", "Default");
  if (auto_selected == "Calibrate Elevator") {
    m_autonomous_command = &m_elevator_calibrate;
  } else if (auto_selected == "Stress Test") {
    m_autonomous_command = &m_stress_test;
  } else if (auto_selected == "Calibrate Drivetrain") {
    m_autonomous_command = &m_drivetrain_calibrate;
  } else if (auto_selected == "Distance PID") {
    m_autonomous_command = &m_distance_pid;
  } else if (auto_selected == "Gyro PID") {
    m_autonomous_command = &m_gyro_pid;
  } else if (auto_selected == "Rocket Pure PID") {
    m_drivetrain.ResetNavX(180);
    m_autonomous_command = &m_hatch_near_rocket;
  } else if (auto_selected == "Rocket Adaptive PID") {
    m_drivetrain.ResetNavX(180);
    m_autonomous_command = &m_rocket_adjustment;
  } else if (auto_selected == "Two Hatch Far Rocket") {
    m_drivetrain.ResetNavX(180);
    m_autonomous_command = &m_far_rocket;
  } else {
    m_drivetrain.ResetNavX(180);
    m_autonomous_command = nullptr;
  }

  m_autonomous_command = m_chooser.GetSelected();

  if (m_autonomous_command == nullptr) {
    Robot::m_macro_superstructure.SetAuto(false);
  } else {
    Robot::m_macro_superstructure.SetAuto(true);
    m_autonomous_command->Start();
  }
}

void Robot::AutonomousPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TeleopInit() {
  if (m_autonomous_command != nullptr) {
    m_autonomous_command->Cancel();
    m_autonomous_command = nullptr;
  }
  Robot::m_macro_superstructure.SetAuto(false);
}

void Robot::TeleopPeriodic() {
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif