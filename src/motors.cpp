#include "main.h"
// #include "settings.h"

/* Controller */
// extern pros::Controller master;

/* Game System Motors */
pros::Motor flywheel(11);
pros::Motor intake(1);

/* Pistons */
pros::ADIDigitalOut expansion1('A');
pros::ADIDigitalOut expansion2('C');

// /* Sensors */
// extern pros::IMU imu_sensor;

// /* Drive */
// extern pros::Motor backLeft;
// extern pros::Motor midLeft;
// extern pros::Motor frontLeft;

// extern pros::Motor backRight;
// extern pros::Motor midRight;
// extern pros::Motor frontRight;