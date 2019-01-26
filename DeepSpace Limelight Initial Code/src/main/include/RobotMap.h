#pragma once

//Controllers
constexpr int driver_port = 0;
constexpr int operator_port = 1;

constexpr double default_driver_deadzone = 0.1;
constexpr double default_operator_deadzone = 0.1;

constexpr int x_axis_left = 0;
constexpr int y_axis_left = 1;
constexpr int left_trigger = 2;
constexpr int right_trigger = 3;
constexpr int x_axis_right = 4;
constexpr int y_axis_right = 5;

//DriveTrain
constexpr int left_front_drive = 1;           //Talon
constexpr int left_back_drive = 2;            //Talon
constexpr int right_front_drive = 3;          //Talon
constexpr int right_back_drive = 4;           //Talon

constexpr int invert_driving_button = 8;      //Start

constexpr int line_sensor_left = 0;           //Digital Input (DIO)
constexpr int line_sensor_middle = 1;         //Digital Input (DIO)
constexpr int line_sensor_right = 2;          //Digital Input (DIO)

//Hatch Pickup and Stick
constexpr int hatch_pickup_rotator = 8;       //Talon
constexpr int hatch_stick_port_start = 0;     //Solenoid
constexpr int hatch_stick_port_end = 1;       //Double Solenoid
constexpr int hatch_stick_button = 7;         //Select

//Ball Intake and Claw
constexpr int ball_claw_left = 5;             //Talon
constexpr int ball_claw_right = 6;            //Talon
constexpr int ball_roller = 7;                //Talon

constexpr int claw_limit_switch = 3;          //Digital Input (DIO)

constexpr int ball_both_intakes_button = 5;   //L
constexpr int ball_both_outtakes_button = 6;  //R
constexpr int ball_claw_intake_button = 1;    //A
constexpr int ball_claw_outtake_button = 2;   //B
constexpr int ball_roller_intake_button = 3;  //X
constexpr int ball_roller_outtake_button = 4; //Y

//Spark Maxes
constexpr int spark_max_test = 9;             //Spark Max