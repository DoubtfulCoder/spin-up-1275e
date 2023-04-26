#include "main.h"
#include "1275.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    // {-18, 20}
    // {18, -20}
    {-18, -19, -20}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    // ,{11, -13}
    ,
    {12, 3, 2}

    // IMU Port
    ,
    4

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    // ,4.125
    ,
    3.25

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    200

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
    // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
    // ,1
    ,
    0.6

    // Uncomment if using tracking wheels
    /*
    // Left Tracking Wheel Ports (negative port will reverse it!)
    // ,{1, 2} // 3 wire encoder
    // ,8 // Rotation sensor

    // Right Tracking Wheel Ports (negative port will reverse it!)
    // ,{-3, -4} // 3 wire encoder
    // ,-9 // Rotation sensor
    */

    // Uncomment if tracking wheels are plugged into a 3 wire expander
    // 3 Wire Port Expander Smart Port
    // ,1
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
    expansion1.set_value(false);
    expansion2.set_value(false);

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
    expansion1.set_value(false);
    expansion2.set_value(false);

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
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);

    bool currently_shooting = false;
    bool currently_indexing = false;
    bool currently_intaking = false;
    bool slow_speed = false;
    bool expansion_value = false;
    bool indexer_value = false;

    bool left_arrow_pressed = false;

    const double FLYWHEEL_SPEED_PERCENT = 0.46;

    while (true)
    {

        // chassis.tank(); // Tank control
        // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
        // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
        // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
        // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

        // Drive
        double x = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        double y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

        // Deadzone
        if (abs(x) < 20)
        {
            x = 0;
        }
        if (abs(y) < 20)
        {
            y = 0;
        }

        // Slow Speed
        if (master.get_digital(DIGITAL_L2))
        {
            slow_speed = true;
        }
        else
        {
            slow_speed = false;
        }

        double multiplier = 1.0;
        if (slow_speed)
        {
            multiplier = 0.2;
        }

        // drive curve
        int neg_x = x < 0 ? -1 : 1;
        int neg_y = y < 0 ? -1 : 1;

        x /= 127;
        y /= 127;

        y = neg_y * y * y;
        x = neg_x * 0.65 * x * x;

        x *= 127;
        y *= 127;

        // Left Side
        frontLeft.move(multiplier * (y + x));
        backLeft.move(multiplier * (y + x));
        midLeft.move(multiplier * (y + x));
        // Right Side
        frontRight.move(multiplier * (y - x));
        backRight.move(multiplier * (y - x));
        midRight.move(multiplier * (y - x));

        // shoot
        if (master.get_digital(DIGITAL_A))
        {
            if (currently_shooting)
            {
                flywheel.move_velocity(0);
                currently_shooting = false;
                printf("This was triggered!\n");
            }
            else
            {
                flywheel.move_velocity(FLYWHEEL_SPEED_PERCENT * -200);
                currently_shooting = true;

                printf("This was triggered 1\n!");
            }
            pros::delay(300);
        }

        printf("Flywheel vel: %d\n", flywheel.get_actual_velocity());

        // intake
        if (master.get_digital(DIGITAL_R2))
        {
            intake.move_velocity(-200);
        }
        else if (master.get_digital(DIGITAL_L1))
        {
            // roller
            intake.move_velocity(200);
        }
        else if (master.get_digital(DIGITAL_R1))
        {
            // indexer
            currently_indexing = true;
            intake.move_velocity(25);
            flywheel.move_velocity(-1 * 200); // move flywheel up to max power
        }
        else
        {
            intake.move_velocity(0);
            if (currently_indexing)
            {
                currently_indexing = false;
                flywheel.move_velocity(FLYWHEEL_SPEED_PERCENT * -200); // move back to normal speed
            }
        }

        // expansion shift key
        if (master.get_digital(DIGITAL_LEFT))
        {
            // shift key for not accidentally activating expansion
            left_arrow_pressed = true;
        }
        // actual expansion
        if (master.get_digital(DIGITAL_RIGHT) && left_arrow_pressed)
        {
            // if (master.get_digital(DIGITAL_LEFT)) {
            // expansion_value = !expansion_value;
            expansion1.set_value(true);
            expansion2.set_value(true);
            pros::delay(3000);
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}
