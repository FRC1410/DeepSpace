#pragma once

#include <frc/commands/Subsystem.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class Limelight : public frc::Subsystem {
  private:
    std::shared_ptr<NetworkTable> limelight_table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

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
};