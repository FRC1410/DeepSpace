#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

#include "RobotMap.h"

class BallClaw : public frc::Subsystem {
  private:
    WPI_TalonSRX m_left_wheel{ball_claw_left};
    WPI_TalonSRX m_right_wheel{ball_claw_right};

    DigitalInput * ball_limit_switch = new DigitalInput(claw_limit_switch);

    double left_speed;
    double right_speed;
    
    bool hooking_left; //TBA
    bool hooking_right; //TBA

  public:
    BallClaw();
    void InitDefaultCommand() override;
    void RunWheels(double speed);
    bool GetLimitSwitch();
    void RunLeftWheels(double speed);
    void RunRightWheels(double speed);
    void RunWheelsIndividual(double left, double right); //for hooking it left/right
    //i realized i broke my elevator theory wait up
  
};