#include "main.h"
#include "1275.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
// const int TURN_SPEED  = 90;
const int TURN_SPEED = 80;
const int SWING_SPEED = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants()
{
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition()
{
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void turn(int degrees)
{
  chassis.reset_pid_targets();  // Resets PID targets to 0
  chassis.reset_gyro();         // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0

  chassis.set_turn_pid(degrees, TURN_SPEED);
  chassis.wait_drive();
}

void spin_roller()
{
  chassis.set_drive_pid(-5, 40);
  intake.move_relative(-810, 200);
  pros::delay(500); // to finish rolling and moving
  // chassis.wait_drive();
}

void spin_roller2()
{
  chassis.set_drive_pid(-5, 30);
  intake.move_relative(-720, 200);
  chassis.wait_drive();
}

void spin_roller_half()
{
  chassis.set_drive_pid(-5, 30);
  intake.move_relative(550, 200);
  pros::delay(500);
}

void drive_example() {}

void rightAuton()
{
  // pros::delay(100000000);
  flywheel.move_velocity(-1 * 200);

  chassis.set_drive_pid(10, DRIVE_SPEED); //
  chassis.wait_drive();

  turn(90);

  intake.move_velocity(-200);

  chassis.set_drive_pid(-15, DRIVE_SPEED); //
  chassis.wait_drive();

  turn(-97);

  chassis.set_drive_pid(7, DRIVE_SPEED); //
  chassis.wait_drive();

  // shoot
  intake.move_velocity(0.07 * 200);
  pros::delay(3250);

  intake.move_velocity(0);

  chassis.set_drive_pid(-7, DRIVE_SPEED); //
  chassis.wait_drive();

  turn(90);

  intake.move_velocity(-200);

  chassis.set_drive_pid(-12, 55); //
  chassis.wait_drive();

  chassis.set_drive_pid(12, DRIVE_SPEED); //
  chassis.wait_drive();

  turn(-97);

  chassis.set_drive_pid(4, DRIVE_SPEED); //
  chassis.wait_drive();

  intake.move_velocity(0.06 * 200);

  pros::delay(1800);

  intake.move_velocity(0);

  flywheel.move_velocity(0);

  turn(-15);

  chassis.set_drive_pid(-24, DRIVE_SPEED); //
  chassis.wait_drive();
  spin_roller();
  pros::delay(10000);
}

void left2()
{
  flywheel.move_velocity(-0.5 * 200);
  spin_roller_half();

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  turn(45);

  // hit them disks
  chassis.set_drive_pid(27, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();

  turn(-75);

  // shoot 2 preloads into high goal
  flywheel.move_velocity(-1 * 200);
  pros::delay(500);
  intake.move_velocity(30);
  pros::delay(2000);

  intake.move_velocity(0);

  // turn to face the disks
  turn(-105);

  // go back and intake them disks
  intake.move_velocity(-100);

  chassis.set_drive_pid(-20, 50); // intake
  chassis.wait_drive();

  pros::delay(2000);

  intake.move_velocity(0);

  // turn to high goal and shoot them disks
  turn(90);
  chassis.set_drive_pid(6.5, DRIVE_SPEED);
  chassis.wait_drive();

  intake.move_velocity(30);

  pros::delay(2500);

  flywheel.move_velocity(0);
}

void left1()
{
  // spin_roller2();

  flywheel.move_velocity(-200);

  // chassis.set_drive_pid(-5, 30);
  // intake.move_relative(-1000, 200);
  // chassis.wait_drive();

  spin_roller_half();
  // pros::delay(2000);

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  turn(45);

  // run intake to hopefully get a 3rd disk as we go back
  intake.move_velocity(-200);

  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  turn(-85);

  chassis.set_drive_pid(7, DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(2000);
  // first shots
  intake.move_velocity(30);

  pros::delay(2000);

  // go back and intake 3 more

  turn(-95);

  intake.move_velocity(-200);

  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();

  // turn and go back to shooting place
  turn(180);

  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();

  turn(95);

  // shoot
  intake.move_velocity(30);
}

///
// Turn Example
///
void turn_example()
{
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}

///
// Combining Turn + Drive
///
void drive_and_turn()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed()
{
  // wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}

///
// Swing Example
///
void swing_example()
{
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}

///
// Auto that tests everything
///
void combining_movements()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Interference example
///
void tug(int attempts)
{
  for (int i = 0; i < attempts - 1; i++)
  {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered)
    {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else
    {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example()
{
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered)
  {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}