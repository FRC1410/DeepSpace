#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "commands/ExampleCommand.h"
#include "commands/MyAutoCommand.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/BallClaw.h"
#include "subsystems/HatchIntake.h"
#include "subsystems/BallIntake.h"

class Robot : public frc::TimedRobot {
  private:
    // Have it null by default so that if testing teleop it
    // doesn't have undefined behavior and potentially crash.
    frc::Command* m_autonomousCommand = nullptr;
    ExampleCommand m_defaultAuto;
    MyAutoCommand m_myAuto;
    frc::SendableChooser<frc::Command*> m_chooser;

  public:
    static ExampleSubsystem m_subsystem;
 	  static DriveTrain m_drivetrain;
	  static OI m_oi;
    static BallClaw m_ball_claw;
    static HatchIntake m_hatch_intake;
    static BallIntake m_ball_intake;
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
