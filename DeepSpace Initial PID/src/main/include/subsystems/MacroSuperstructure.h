#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Spark.h>
#include <frc/WPILib.h>

#include "RobotMap.h"

class MacroSuperstructure : public frc::Subsystem {
  private:
    int profile = 0;
    bool reset = false;

    frc::Spark LEDs{LED_controller_port};

    bool running_auto;

    //Compressor * compress = new Compressor(0);

  public:
    MacroSuperstructure();
    void InitDefaultCommand() override;
    void SetProfile(int direction);
    int GetProfile();
    bool GetReset();
    void RunLEDs(double value);
    void SetAuto(bool auto_input);
    bool GetAuto();
    void StartCompressor();
    void StopCompressor();    
};