#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/Smartdashboard.h>
#include <wpi/raw_ostream.h>
#include <cameraserver/CameraServer.h>
#include <frc/WPILib.h>

#include "RobotMap.h"
#include "OI.h"

#include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/HatchStick.h"
#include "subsystems/BallClaw.h"
#include "subsystems/BallRoller.h"
#include "subsystems/SparkMax.h"
#include "subsystems/Limelight.h"

#include "commands/ExampleCommand.h"
#include "commands/MyAutoCommand.h"
#include "commands/AutoLineSensor.h"
#include "commands/AutoLimelightTargeting.h"

class Robot : public frc::TimedRobot {
  private:
    // Have it null by default so that if testing teleop it
    // doesn't have undefined behavior and potentially crash.
    frc::Command* m_autonomous_command = nullptr;
    ExampleCommand m_defaultAuto;
    MyAutoCommand m_myAuto;
    AutoLineSensor m_auto_line_sensor;
    AutoLimelightTargeting m_auto_limelight_targeting;

    frc::SendableChooser<frc::Command*> m_chooser;

  public:
    static ExampleSubsystem m_subsystem;
    static OI m_oi;
 	  static DriveTrain m_drivetrain;
    static HatchPickup m_hatch_pickup;
    static HatchStick m_hatch_stick;
    static BallRoller m_ball_roller;
    static BallClaw m_ball_claw;
    static SparkMax m_spark_max;
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
