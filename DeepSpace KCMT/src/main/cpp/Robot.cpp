/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

OI Robot::m_oi;
MacroSuperstructure Robot::m_macro_superstructure;
DriveTrain Robot::m_drivetrain;
BallClaw Robot::m_ball_claw;
BallRoller Robot::m_ball_roller;
HatchStick Robot::m_hatch_stick;
Elevator Robot::m_elevator;
Limelight Robot::m_limelight;

void Robot::RobotInit() {
  m_ball_roller.RollerUp();
  m_hatch_stick.RetractStick();
  m_macro_superstructure.SetCompressor(true);

  m_chooser.SetDefaultOption("Do Nothing", nullptr);
  m_chooser.AddOption("Distance PID", &m_distance_pid);
  m_chooser.AddOption("Gyro PID", &m_gyro_pid);
  m_chooser.AddOption("Rocket Pure PID", &m_hatch_near_rocket);
  m_chooser.AddOption("Rocket Adaptive PID", &m_rocket_adjustment);
  m_chooser.AddOption("Calibrate Elevator", &m_elevator_calibrate);
  m_chooser.AddOption("Calibrate Drivetrain", &m_drivetrain_calibrate);
  m_chooser.AddOption("Stress Test", &m_stress_test);
  m_chooser.AddOption("Two Hatch Far Rocket", &m_far_rocket);

  frc::Shuffleboard::GetTab("Drivers").Add("Auto", m_chooser).WithWidget(frc::BuiltInWidgets::kComboBoxChooser).WithPosition(2, 1).WithSize(1, 1);
  frc::SmartDashboard::PutData("Auto", &m_chooser);
  frc::SmartDashboard::PutBoolean("Auto Inverter", false);
}

void Robot::RobotPeriodic() {}

void Robot::DisabledInit() {
  m_oi.SetDriverRumble(0, 0);
  m_oi.SetOperatorRumble(0, 0);
  m_limelight.SetPipeline(limelight_driver_pipeline);
}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
  m_macro_superstructure.SetFMSAuto(true);
  m_macro_superstructure.SetInvertedAuto(shuffleboard_auto_inverter.GetBoolean(false));

  m_drivetrain.ResetEncoders();
  m_drivetrain.ResetNavX(180);
  m_elevator.ResetEncoders();
  
  m_drivetrain.SetX(-47 * Robot::m_macro_superstructure.GetInvertedAuto());
  m_drivetrain.SetZ(67);

  m_drivetrain.ResetTime();

  m_drivetrain.SetSpeed(0, 0);
  m_elevator.RunElevator(0);

  m_limelight.SetPipeline(limelight_driver_pipeline);

  m_drivetrain.ResetDistanceIntegral();
  m_drivetrain.ResetGyroIntegral();
  m_elevator.ResetIntegral();
  m_limelight.ResetAngleIntegral();
  m_limelight.ResetAreaIntegral();
  m_limelight.ResetDistanceIntegral();
  
  if (m_chooser.GetSelected() == &m_far_rocket) {
    m_drivetrain.ResetNavX(0);
  }

  //m_autonomous_command = m_chooser.GetSelected();
  m_autonomous_command = nullptr;

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
  m_drivetrain.ResetDistanceIntegral();
  m_drivetrain.ResetGyroIntegral();
  m_elevator.ResetIntegral();
  m_limelight.ResetAngleIntegral();
  m_limelight.ResetAreaIntegral();
  m_limelight.ResetDistanceIntegral();

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