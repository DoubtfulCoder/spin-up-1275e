#pragma once

#include "EZ-Template/drive/drive.hpp"
#include "pros/motors.hpp"

extern Drive chassis;
extern pros::Motor flywheel;
extern pros::Motor intake;

void rightAuton();
void left1();
void left2();
void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();

void autontas();