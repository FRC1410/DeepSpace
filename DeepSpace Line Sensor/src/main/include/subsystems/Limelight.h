#pragma once

#include <frc/commands/Subsystem.h>
#include <networktables/NetworkTable.h>

class Limelight : public frc::Subsystem {
  private:
    //std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  public:
    Limelight();
    void InitDefaultCommand() override;
};
