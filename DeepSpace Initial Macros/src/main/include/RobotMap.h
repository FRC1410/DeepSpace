#pragma once

//Controllers
constexpr int driver_port = 0;
constexpr int operator_port = 1;

constexpr double default_driver_deadzone = 0.15;
constexpr double default_operator_deadzone = 0.2;

//DriveTrain
constexpr int left_front_drive = 1;               //Talon
constexpr int left_middle_drive = 2;              //Talon
constexpr int left_back_drive = 3;                //Talon
constexpr int right_front_drive = 4;              //Talon
constexpr int right_middle_drive = 5;             //Talon
constexpr int right_back_drive = 6;               //Talon

constexpr int drivetrain_left_axis = 1;           //Left Stick Y-Axis
constexpr int drivetrain_right_axis = 5;          //Right Stick Y-Axis
constexpr int invert_driving_button = 5;          //L

constexpr int line_sensor_left = 0;               //Digital Input (DIO)
constexpr int line_sensor_middle = 1;             //Digital Input (DIO)
constexpr int line_sensor_right = 2;              //Digital Input (DIO)

//Ball Roller and Claw
constexpr int ball_claw_left = 7;                 //Talon
constexpr int ball_claw_right = 8;                //Talon
constexpr int ball_roller = 9;                    //Talon

constexpr int ball_roller_rotator_port_start = 0; //Double Solenoid
constexpr int ball_roller_rotator_port_end = 1;   //Double solenoid

constexpr int claw_limit_switch = 3;              //Digital Input (DIO)

constexpr int ball_both_intakes_axis = 3;         //Right Trigger
constexpr int ball_both_outtakes_axis = 2;        //Left Trigger
constexpr int ball_claw_left_outtake_axis = 2;    //Left Trigger
constexpr int ball_claw_right_outtake_axis = 3;   //Right Trigger
constexpr int ball_roller_rotator_button = 6;     //R
 
//Hatch Pickup and Stick
constexpr int hatch_pickup_rotator = 10;          //Talon

constexpr int hatch_stick_port_start = 2;         //Double Solenoid
constexpr int hatch_stick_port_end = 3;           //Double Solenoid

constexpr int hatch_pickup_rotator_axis = 5;      //Right Stick Y-Axis
constexpr int hatch_pickup_rotator_button = 6;    //R
constexpr int hatch_stick_button = 5;             //L

//Elevator
constexpr int elevator_left_motor = 11;           //Spark Max
constexpr int elevator_right_motor = 12;          //Spark Max

constexpr int elevator_limit_switch = 4;          //Digital Input (DIO)

constexpr int elevator_axis = 1;                  //Left Stick Y-Axis
constexpr int elevator_low_position = 1;          //A
constexpr int elevator_mid_low_position = 3;      //X
constexpr int elevator_mid_position = 2;          //B
constexpr int elevator_high_position = 4;         //Y

constexpr int elevator_max_height = 78;
//constexpr int elevator_max_revolutions = 

//Climber
constexpr int climber_front_port_start = 4;       //Double Solenoid
constexpr int climber_front_port_end = 5;         //Double Solenoid
constexpr int climber_back_port_start = 6;        //Double Solenoid
constexpr int climber_back_port_end = 7;          //Double Solenoid

constexpr int climber_front_button = 1;           //A
constexpr int climber_back_button = 4;            //Y

//LEDs
constexpr int LED_controller_port = 0;            //PWM

constexpr double cargo_color = 0.63;
constexpr double hatch_color = 0.69;
constexpr double climber_color = 0.89;
constexpr double reset_mechanisms_color = 0.75;

//Profile Changes
constexpr int ball_profile_direction = 0;         //D-Pad Up
constexpr int hatch_profile_direction = 270;      //D-Pad Left
constexpr int climber_profile_direction = 90;     //D-Pad Right
constexpr int reset_mechanisms_direction = 180;   //D-Pad Down

constexpr int hatch_profile_number = 0;
constexpr int ball_profile_number = 1;
constexpr int climber_profile_number = 2;

//Safety
constexpr int manual_control_button = 7;          //Back
constexpr int toggle_compressor_button = 8;       //Start