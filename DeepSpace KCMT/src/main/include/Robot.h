/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include "OI.h"

#include "subsystems/DriveTrain.h"
#include "subsystems/HatchStick.h"
#include "subsystems/BallClaw.h"
#include "subsystems/BallRoller.h"
#include "subsystems/Elevator.h"
#include "subsystems/Limelight.h"
#include "subsystems/MacroSuperstructure.h"

#include "commands/Auto/AutoTwoHatchFarRocket.h"
#include "commands/Auto/AutoRocketAdjustment.h"
#include "commands/Auto/AutoHatchNearRocket.h"
#include "commands/Auto/AutoDistancePID.h"
#include "commands/Auto/AutoGyroPID.h"
#include "commands/Auto/AutoElevatorCalibrate.h"
#include "commands/Auto/AutoDrivetrainCalibrate.h"
#include "commands/Auto/AutoStressTest.h"

class Robot : public frc::TimedRobot {
  private:
    frc::Command* m_autonomous_command = nullptr;
    frc::SendableChooser<frc::Command*> m_chooser;

    AutoTwoHatchFarRocket m_far_rocket;
    AutoRocketAdjustment m_rocket_adjustment;
    AutoHatchNearRocket m_hatch_near_rocket;
    AutoDistancePID m_distance_pid;
    AutoGyroPID m_gyro_pid;
    AutoStressTest m_stress_test;
    AutoElevatorCalibrate m_elevator_calibrate;
    AutoDrivetrainCalibrate m_drivetrain_calibrate;

    nt::NetworkTableEntry shuffleboard_auto_inverter = frc::Shuffleboard::GetTab("Drivers").Add("Auto Inverter", false).WithWidget(frc::BuiltInWidgets::kToggleButton).WithPosition(2, 2).WithSize(1, 1).GetEntry();

  public:
    bool auto_running = false;

    static OI m_oi;
    static MacroSuperstructure m_macro_superstructure;
 	  static DriveTrain m_drivetrain;
    static BallClaw m_ball_claw;
    static BallRoller m_ball_roller;
    static HatchStick m_hatch_stick;
    static Elevator m_elevator;
    static Limelight m_limelight;

    void RobotInit() override;
    void RobotPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
};