/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"
#include "commands/ElevatorRun.h"

Elevator::Elevator() : Subsystem("ExampleSubsystem") {}

void Elevator::InitDefaultCommand() {
  SetDefaultCommand(new ElevatorRun());
}

void Elevator::RunElevator(double speed) {
  m_elevator_left.Set(speed);
  m_elevator_right.Set(-speed);
}

double Elevator::GetLeftRevolutions() {
  return m_left_encoder.GetPosition();
}

double Elevator::GetRightRevolutions() {
  return m_right_encoder.GetPosition();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
