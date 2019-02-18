/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/Smartdashboard.h>
#include <frc/WPILib.h>

#include "RobotMap.h"
#include "OI.h"

#include "subsystems/DriveTrain.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/HatchStick.h"
#include "subsystems/BallClaw.h"
#include "subsystems/BallRoller.h"
#include "subsystems/Elevator.h"
#include "subsystems/Limelight.h"
#include "subsystems/MacroSuperstructure.h"
#include "subsystems/Climber.h"

#include "commands/AutoLimelightTargeting.h"
#include "commands/AutoGyroPID.h"
#include "commands/AutoElevatorCalibrate.h"
#include "commands/AutoStressTest.h"
#include "commands/AutoDrivetrainCalibrate.h"

class Robot : public frc::TimedRobot {
  private:
    frc::Watchdog m_watchdog{1, nullptr};
    frc::Timer m_timer;

    frc::Command* m_autonomous_command = nullptr;
    AutoLimelightTargeting m_auto_limelight_targeting;
    AutoGyroPID m_auto_gyro_pid;
    AutoElevatorCalibrate m_elevator_calibrate;
    AutoStressTest m_stress_test;
    AutoDrivetrainCalibrate m_drivetrain_calibrate;

    frc::SendableChooser<frc::Command*> m_chooser;

  public:
    bool auto_running = false;

    static OI m_oi;
    static MacroSuperstructure m_macro_superstructure;
 	  static DriveTrain m_drivetrain;
    static BallClaw m_ball_claw;
    static BallRoller m_ball_roller;
    static HatchPickup m_hatch_pickup;
    static HatchStick m_hatch_stick;
    static Elevator m_elevator;
    static Climber m_climber;
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