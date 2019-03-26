/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

constexpr double pi = 3.14159265358979324;

//Controllers
constexpr int driver_port = 0;                          //Driver Station
constexpr int operator_port = 1;                        //Driver Station
constexpr int human_player_port = 2;                    //Driver Station

constexpr double driver_deadzone = 0.0;                //Joystick Deadzone
constexpr double operator_deadzone = 0.2;               //Joystick Deadzone

//DriveTrain
constexpr int left_front_drive = 1;                     //Talon
constexpr int left_middle_drive = 2;                    //Talon
constexpr int left_back_drive = 3;                      //Talon
constexpr int right_front_drive = 4;                    //Talon
constexpr int right_middle_drive = 5;                   //Talon
constexpr int right_back_drive = 6;                     //Talon

constexpr int drivetrain_left_axis = 1;                 //Left Stick Y-Axis
constexpr int drivetrain_right_axis = 5;                //Right Stick Y-Axis
constexpr int invert_driving_button = 5;                //L
constexpr int vision_align_button = 6;                  //R

constexpr double drivetrain_distance_kP = 0.0135;       //PID Tuning
constexpr double drivetrain_distance_kI = 0;            //PID Tuning
constexpr double drivetrain_distance_kD = 0;            //PID Tuning

constexpr double drivetrain_gyro_kP = 0.03;             //PID Tuning was 0.019
constexpr double drivetrain_gyro_kI = 0;                //PID Tuning
constexpr double drivetrain_gyro_kD = 0;                //PID Tuning

constexpr double drivetrain_gyro_deadband = 2;          //Auto staging

constexpr double drivetrain_acceleration_time = 1;      //0 to max speed
constexpr double drivetrain_friction = 0.4;             //Power required to move robot
constexpr double drivetrain_friction_deadband = 0.1;    //Jumper Size

constexpr double drivetrain_max_speed = 200;            //Inches per second
constexpr double drivetrain_driftiness = 0.5;           //Turning Efficiency
constexpr double drivetrain_radius = 11;                //Middle of chassis to wheel
constexpr double drivetrain_motion_profile_tolerance = 0.03125;

//Ball Roller and Claw
constexpr int ball_claw_left = 7;                       //Talon
constexpr int ball_claw_right = 8;                      //Talon
constexpr int ball_roller = 9;                          //Talon

constexpr int ball_roller_rotator_port_start = 3;       //Double Solenoid
constexpr int ball_roller_rotator_port_end = 4;         //Double solenoid

constexpr int claw_limit_switch = 3;                    //Digital Input (DIO)

constexpr int ball_both_intakes_axis = 3;               //Right Trigger
constexpr int ball_both_outtakes_axis = 2;              //Left Trigger
constexpr int ball_claw_left_outtake_axis = 2;          //Left Trigger
constexpr int ball_claw_right_outtake_axis = 3;         //Right Trigger
constexpr int ball_roller_rotator_button = 6;           //R
 
//Hatch Pickup and Stick
constexpr int hatch_pickup_rotator = 10;                //Talon

constexpr int hatch_stick_port_start = 0;               //Double Solenoid
constexpr int hatch_stick_port_end = 7;                 //Double Solenoid

constexpr int pressure_sensor = 0;                      //Analog Input

constexpr int hatch_pickup_rotator_axis = 5;            //Right Stick Y-Axis
constexpr int hatch_pickup_rotator_button = 6;          //R
constexpr int hatch_stick_button = 5;                   //L
constexpr int hatch_pickup_toggle_button = 6;           //Hatch handoff button

constexpr double hatch_pickup_up_position = 0.05;       //Encoder when raised
constexpr double hatch_pickup_down_position = 0.75;     //Encoder when lowered

constexpr double hatch_handoff_time = 0.3;              //Time rotator spends pushing on stick
constexpr double hatch_pickup_down_power = 0.5;         //Handoff Power
constexpr double hatch_pickup_up_power = -0.45;         //Handoff Power
constexpr double hatch_pickup_stall_power = 0.05;       //Power when down

constexpr double hatch_pickup_kP = 0.8;                 //PID Tuning
constexpr double hatch_pickup_kI = 0.1;                 //PID Tuning
constexpr double hatch_pickup_kD = 0;                   //PID Tuning

//Elevator
constexpr int elevator_left_motor = 11;                 //Spark Max
constexpr int elevator_right_motor = 12;                //Spark Max

constexpr int elevator_axis = 1;                        //Left Stick Y-Axis
constexpr int elevator_low_position_button = 1;         //A
constexpr int elevator_mid_position_button = 2;         //B
constexpr int elevator_high_position_button = 4;        //Y
constexpr int elevator_loading_station_button = 3;      //X

constexpr double elevator_ball_displacement = -1.75;    //Center of Ball
constexpr double elevator_hatch_displacement = 7;       //Center of Hatch

constexpr double elevator_low_hatch_height = 24.5 - elevator_hatch_displacement;
constexpr double elevator_mid_hatch_height = 51 - elevator_hatch_displacement;
constexpr double elevator_high_hatch_height = 75 - elevator_hatch_displacement;

constexpr double elevator_handoff_height = 25.4 - elevator_hatch_displacement;
constexpr double elevator_handoff_raise = 13;

constexpr double elevator_loading_station_displacement = 7;

constexpr double elevator_low_ball_height = 29 - elevator_ball_displacement;
constexpr double elevator_mid_ball_height = 55.5 - elevator_ball_displacement;
constexpr double elevator_high_ball_height = 72 - elevator_ball_displacement;
constexpr double elevator_cargo_ship_height = 42.0 - elevator_ball_displacement;

constexpr double elevator_calibration_height = 67.5;    //Height Calibration, top of carriage
constexpr double elevator_calibration_revolutions = 32; //Height Calibration
constexpr double elevator_min_height = 9.25;            //Top of Carriage
constexpr double elevator_max_height = 86;              //Max Height

constexpr double lower_intake_intersect_height = 15;    //Intersection between ball claw and roller
constexpr double upper_intake_intersect_height = 20;    //Intersection between ball claw and roller

constexpr double elevator_acceleration_time = 2;      //Stationary to max speed
constexpr double elevator_gravity = 0.045;              //Power required to keep carriage stable

constexpr double elevator_max_velocity = 120;           //Inches per second up without game piece
constexpr double elevator_limiter = 0.5;                //Max power before PID

constexpr double elevator_bottom_buffer = 2.5;          //Inches to bottom, no power inputted
constexpr double elevator_deadband = 1.2;               //Range of stalling, inches

constexpr double elevator_kP = 0.02;                   //PID Tuning
constexpr double elevator_kI = 0.0;                   //PID Tuning
constexpr double elevator_kD = 0.0;                     //PID Tuning  

//Climber
constexpr int climber_front_port_start = 1;             //Double Solenoid
constexpr int climber_front_port_end = 6;               //Double Solenoid
constexpr int climber_back_port_start = 2;              //Double Solenoid
constexpr int climber_back_port_end = 5;                //Double Solenoid

constexpr int climber_front_button = 1;                 //A
constexpr int climber_back_button = 4;                  //Y

//LEDs
constexpr int left_LED_controller_port = 0;             //PWM
constexpr int right_LED_controller_port = 1;            //PWM

constexpr int LED_cycle_negative_button = 5;            //L
constexpr int LED_cycle_positive_button = 6;            //R

constexpr double hatch_color = 0.69;                    //Yellow
constexpr double ball_color = 0.63;                     //Orange
constexpr double climber_color = 0.89;                  //Purple
constexpr double reset_mechanisms_color = 0.87;         //Blue
constexpr double ball_acquired_color = 0.93;            //White
constexpr double vision_targeting_color = 0.75;         //Green
constexpr double encoder_fail_color = 0.59;             //Red

constexpr double blinking_LED_time = 0.15;         //Blinks three times

//Profile Changes
constexpr int ball_profile_direction = 0;               //D-Pad Up
constexpr int hatch_profile_direction = 270;            //D-Pad Left
constexpr int climber_profile_direction = 90;           //D-Pad Right
constexpr int reset_mechanisms_direction = 180;         //D-Pad Down

constexpr int hatch_profile_number = 0;                 //Operator Profiles
constexpr int ball_profile_number = 1;                  //Operator Profiles
constexpr int climber_profile_number = 2;               //Operator Profiles

//Limelight
constexpr int limelight_toggle_button = 1;              //A

constexpr double limelight_x_offset = 9.5;              //Right of center of rotation
constexpr double limelight_z_offset = 1;                //Infront of center of rotation
constexpr double limelight_angle_offset = 14;         //Tilted Left

constexpr double limelight_kP = 1;                      //PID for desired angle
constexpr double limelight_kI = 0;                      //PID for desired angle
constexpr double limelight_kD = 0;                      //PID for desired angle

//Safety
constexpr int operator_macro_override_button = 7;       //Back
constexpr int toggle_compressor_button = 8;             //Start
constexpr int encoder_fail_safety = 5;

constexpr double single_rumble_time = 0.25;             //Rumble Timings
constexpr double double_rumble_time = 0.15;             //Rumble Timings
constexpr double long_rumble_time = 0.7;                //Rumble Timings;

constexpr bool debugging = false;                       //Shuffleboard

constexpr double compressor_low_thresh = 40;            //Sets the compressor autotrigger threshold
constexpr double compressor_high_thresh = 80;           //Sets the compressor autotrigger off threshold