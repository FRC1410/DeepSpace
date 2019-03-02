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

  public:
    Limelight();
    void InitDefaultCommand() override;
    double GetTarget();
    double GetTargetX();
    double GetTargetY();
    double GetTargetArea();
    double GetTargetSkew();
    double GetCameraLatency();
    void TurnOffLights();
    void TurnOnLights();
    void SetPipeline(int pipeline);
    double GetTargetXTrans();
    double GetTargetZTrans();
    double GetTargetAngleTrans();
    int GetCamtranSize();
    double GetRandyZ();
    double GetRandyX();
    double GetPID(double preivous_error, double time_difference);
    double GetChassisX();
    double GetChassisZ();
    double GetChassisAngle();
    double ResetIntegral();
};