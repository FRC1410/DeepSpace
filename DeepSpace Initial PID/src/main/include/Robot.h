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

#include "subsystems/DriveTrain.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/HatchStick.h"
#include "subsystems/BallClaw.h"
#include "subsystems/BallRoller.h"
#include "subsystems/Elevator.h"
#include "subsystems/Limelight.h"
#include "subsystems/MacroSuperstructure.h"
#include "subsystems/Climber.h"

#include "commands/AutoLineSensor.h"
#include "commands/AutoLimelightTargeting.h"
#include "commands/AutoElevatorAccelerate.h"
#include "commands/AutoGyroPID.h"

class Robot : public frc::TimedRobot {
  private:
    // Have it null by default so that if testing teleop it
    // doesn't have undefined behavior and potentially crash.
    frc::Command* m_autonomous_command = nullptr;
    AutoLineSensor m_auto_line_sensor;
    AutoLimelightTargeting m_auto_limelight_targeting;
    AutoElevatorAccelerate m_auto_elevator_accelerate;
    AutoGyroPID m_auto_gyro_pid;

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