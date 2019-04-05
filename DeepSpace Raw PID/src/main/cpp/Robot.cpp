/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

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
  m_ball_roller.RollerUp();
  m_hatch_stick.RetractStick();
  m_climber.RetractFront();
  m_climber.RetractBack();

  m_chooser.SetDefaultOption("Do Nothing", nullptr);
  m_chooser.AddOption("Distance PID", &m_distance_pid);
  m_chooser.AddOption("Gyro PID", &m_gyro_pid);
  m_chooser.AddOption("Rocket Pure PID", &m_hatch_near_rocket);
  m_chooser.AddOption("Rocket Adaptive PID", &m_rocket_adjustment);
  m_chooser.AddOption("Calibrate Elevator", &m_elevator_calibrate);
  m_chooser.AddOption("Calibrate Drivetrain", &m_drivetrain_calibrate);
  m_chooser.AddOption("Stress Test", &m_stress_test);
  m_chooser.AddOption("Two Hatch Far Rocket", &m_far_rocket);
  frc::SmartDashboard::PutData("Auto", &m_chooser);

  frc::SmartDashboard::PutBoolean("Auto Inverter", false);

  nt::NetworkTableEntry shuffleboard_hatch = frc::Shuffleboard::GetTab("Drivers").Add("Hatch", false).WithWidget("Boolean Box").GetEntry();
  nt::NetworkTableEntry shuffleboard_cargo = frc::Shuffleboard::GetTab("Drivers").Add("Cargo", false).WithWidget("Boolean Box").GetEntry();
  nt::NetworkTableEntry shuffleboard_climber = frc::Shuffleboard::GetTab("Drivers").Add("Climber", false).WithWidget("Boolean Box").GetEntry();
  nt::NetworkTableEntry shuffleboard_voltage = frc::Shuffleboard::GetTab("Drivers").Add("Voltage", 0).WithWidget("Voltage View").GetEntry();
  nt::NetworkTableEntry shuffleboard_time = frc::Shuffleboard::GetTab("Drivers").Add("Time", 0).WithWidget("Number Bar").GetEntry();
  nt::NetworkTableEntry shuffleboard_warnings = frc::Shuffleboard::GetTab("Drivers").Add("Warnings", 0).WithWidget("Boolean Box").GetEntry();
  nt::NetworkTableEntry shuffleboard_auto_inverter = frc::Shuffleboard::GetTab("Drivers").Add("Auto Inverter", 0).WithWidget("Toggle Button").GetEntry();
  nt::NetworkTableEntry shuffleboard_pressure = frc::Shuffleboard::GetTab("Drivers").Add("Pressure", 0).WithWidget("Toggle Button").GetEntry();
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
  m_oi.SetDriverRumbleLeft(0);
  m_oi.SetDriverRumbleRight(0);
  m_oi.SetOperatorRumbleLeft(0);
  m_oi.SetOperatorRumbleRight(0);
  m_limelight.TurnOffLights();
  m_limelight.SetPipeline(0);
}

void Robot::DisabledPeriodic() { 
  Robot::m_limelight.TurnOffLights();
  frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
  m_macro_superstructure.SetFMSAuto(true);

  m_macro_superstructure.SetInvertedAuto(frc::SmartDashboard::GetBoolean("Auto Inverter", false));

  m_drivetrain.ResetEncoders();
  m_elevator.ResetEncoders();
  m_hatch_pickup.ResetEncoder();
  m_drivetrain.ResetNavX(0);
  
  m_drivetrain.SetX(-47 * Robot::m_macro_superstructure.GetInvertedAuto());
  m_drivetrain.SetZ(67);

  m_drivetrain.ResetDistanceIntegral();
  m_drivetrain.ResetGyroIntegral();
  m_drivetrain.ResetTime();

  m_drivetrain.SetSpeed(0, 0);
  m_elevator.RunElevator(0);

  m_limelight.TurnOnLights();
  m_limelight.SetPipeline(2);
  
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
    m_macro_superstructure.SetAuto(false);
  } else {
    m_macro_superstructure.SetAuto(true);
    m_autonomous_command->Start();
  }
}

void Robot::AutonomousPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TeleopInit() {
  m_macro_superstructure.SetFMSAuto(false);

  if (m_autonomous_command != nullptr) {
    m_autonomous_command->Cancel();
    m_autonomous_command = nullptr;
  }
  m_macro_superstructure.SetAuto(false);
}

void Robot::TeleopPeriodic() {
  frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif