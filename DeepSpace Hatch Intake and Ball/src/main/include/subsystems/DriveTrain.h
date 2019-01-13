#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

#include "RobotMap.h"
#include "commands/Drive.h"

class DriveTrain : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_front{left_front_drive};
    WPI_TalonSRX m_left_back{left_back_drive};
    WPI_TalonSRX m_right_front{right_front_drive};
    WPI_TalonSRX m_right_back{right_back_drive};

    frc::DifferentialDrive m_front{m_left_front, m_right_front};
    frc::DifferentialDrive m_back{m_left_back, m_right_back};
  public:
    DriveTrain();
    void InitDefaultCommand() override;
    void TankDrive(double left, double right);
};