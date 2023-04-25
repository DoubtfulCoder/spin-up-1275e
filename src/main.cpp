#include "main.h"
#include "1275.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
Drive chassis(
    {-18, -19, -20},
    {12, 3, 2},
    4,
    3.25,
    200,
    0.6

);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
  // Set expansion pistons down
  expansion1.set_value(true);
  expansion2.set_value(true);

  pros::delay(500);

  // Print our branding over your terminal :D
  ez::print_ez_template();

  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0);                       // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0);                   // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  default_constants();                               // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults();                         // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
      Auton("Left auton", left2),
      Auton("Example Drive\n\nDrive forward and come back.", left2),
      Auton("Example Turn\n\nTurn 3 times.", left1),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
  // Set expansion pistons down
  expansion1.set_value(true);
  expansion2.set_value(true);

  pros::delay(500);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  chassis.reset_pid_targets();               // Resets PID targets to 0
  chassis.reset_gyro();                      // Reset gyro position to 0
  chassis.reset_drive_sensor();              // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}

/**
 * Opcontrol
 * Original: doubtfulguy
 * Refactored: piman51277
 */
void opcontrol()
{
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  // slow speed flag
  bool slowSpeedEnabled = false;
  bool expansionEnabled = false;

  // flywheel constants
  const float FLYWHEEL_IDLE = 0 * -200;
  const float FLYWHEEL_SHOOT = 0.75 * -200;
  const float FLYWHEEL_MAX = 1.0 * -200;

  // main op loop
  while (true)
  {

    // Drive control

    // get joystick values
    int joyX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int joyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    // deadzone n<20
    joyX = std::abs(joyX) < 20 ? 0 : joyX;
    joyY = std::abs(joyY) < 20 ? 0 : joyY;

    // applies a power curve while preserving direction
    joyX = (joyX < 0 ? -1 : 1) * 0.65 * joyX * joyX;
    joyY = (joyY < 0 ? -1 : 1) * joyY * joyY;

    // compute motor power
    int slowSpeedMultipler = slowSpeedEnabled ? 0.2 : 1.0;
    int leftSidePower = slowSpeedMultipler * (joyY + joyX);
    int rightSidePower = slowSpeedMultipler * (joyY - joyX);

    // set motor power
    frontLeft.move(leftSidePower);
    backLeft.move(leftSidePower);
    midLeft.move(leftSidePower);
    frontRight.move(rightSidePower);
    backRight.move(rightSidePower);
    midRight.move(rightSidePower);

    // slow speed
    slowSpeedEnabled = master.get_digital(DIGITAL_L2);

    // flywheel speed control
    if (master.get_digital(DIGITAL_R1))
    {
      flywheel.move(FLYWHEEL_MAX);
    }
    else if (master.get_digital(DIGITAL_L1))
    {
      flywheel.move(FLYWHEEL_SHOOT);
    }
    else
    {
      flywheel.move(FLYWHEEL_IDLE);
    }

    // intake control
    if (master.get_digital(DIGITAL_R2))
    {
      intake.move(-127);
    }
    else if (master.get_digital(DIGITAL_A))
    {
      intake.move(100);
    }
    else
    {
      intake.move(0);
    }

    // expansion
    if (master.get_digital(DIGITAL_LEFT) && master.get_digital(DIGITAL_RIGHT))
    {
      expansionEnabled = true;
    }

    if (expansionEnabled)
    {
      expansion1.set_value(false);
      expansion2.set_value(false);
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}