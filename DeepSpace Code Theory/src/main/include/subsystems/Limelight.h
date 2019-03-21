/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class Limelight : public frc::Subsystem {
  private:
    std::shared_ptr<NetworkTable> limelight_table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

    double error, P, D;
    double I = 0;
    double previous_error = 0;

    int current_profile;

  public:
    Limelight();
    void InitDefaultCommand() override;

    bool GetTarget();
    double GetTargetX();
    double GetTargetY();
    double GetTargetWidth();
    double GetTargetHeight();
    double GetCameraLatency();

    void TurnOffLights();
    void TurnOnLights();
    void SetPipeline(int pipeline);
    int GetPipeline();

    double GetLimelightAngle();
    double GetLimelightX();
    double GetLimelightZ();

    double GetChassisAngle();
    double GetChassisX();
    double GetChassisZ();

    double GetPID(double position, double time_difference);
    double ResetIntegral();
};