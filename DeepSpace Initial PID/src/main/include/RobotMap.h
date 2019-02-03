#pragma once

constexpr double pi = 3.14159265358979324;

//Controllers
constexpr int driver_port = 0;
constexpr int operator_port = 1;

constexpr double driver_deadzone = 0.1;
constexpr double operator_deadzone = 0.2;

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

constexpr int line_sensor_left = 2;               //Digital Input (DIO)
constexpr int line_sensor_middle = 1;             //Digital Input (DIO)
constexpr int line_sensor_right = 0;              //Digital Input (DIO)

constexpr double drivetrain_distance_kP = 0;      //PID Tuning
constexpr double drivetrain_distance_kI = 0;      //PID Tuning
constexpr double drivetrain_distance_kD = 0;      //PID Tuning

constexpr double drivetrain_gyro_kP = 0.015;      //PID Tuning
constexpr double drivetrain_gyro_kI = 0.01;       //PID Tuning
constexpr double drivetrain_gyro_kD = 0;          //PID Tuning

constexpr double drivetrain_acceleration_time = 1;
constexpr double mechanical_deadzone = 0.3;

//Ball Roller and Claw
constexpr int ball_claw_left = 7;                 //Talon
constexpr int ball_claw_right = 8;                //Talon
constexpr int ball_roller = 9;                    //Talon

constexpr int ball_roller_rotator_port_start = 3; //Double Solenoid
constexpr int ball_roller_rotator_port_end = 4;   //Double solenoid

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

constexpr double hatch_pickup_kP = 0;  
constexpr double hatch_pickup_kI = 0; 
constexpr double hatch_pickup_kD = 0; 

//Elevator
constexpr int elevator_left_motor = 11;           //Spark Max
constexpr int elevator_right_motor = 12;          //Spark Max

constexpr int elevator_limit_switch = 4;          //Digital Input (DIO)

constexpr int elevator_axis = 1;                    //Left Stick Y-Axis
constexpr int elevator_low_position_button = 1;     //A
constexpr int elevator_mid_low_position_button = 3; //X
constexpr int elevator_mid_position_button = 2;     //B
constexpr int elevator_high_position_button = 4;    //Y

constexpr double elevator_max_height = 81.5;
constexpr double elevator_min_height = 10;
constexpr double elevator_max_revolutions = 40;
constexpr double elevator_accleration_time = 0.5;
constexpr double elevator_weak_gravity = 0.03;
constexpr double elevator_strong_gravity = 0.06;

constexpr double elevator_kP = 0;                 //PID Tuning
constexpr double elevator_kI = 0;                 //PID Tuning
constexpr double elevator_kD = 0;                 //PID Tuning

//Climber
constexpr int climber_front_port_start = 1;       //Double Solenoid
constexpr int climber_front_port_end = 6;         //Double Solenoid
constexpr int climber_back_port_start = 2;        //Double Solenoid
constexpr int climber_back_port_end = 5;          //Double Solenoid

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