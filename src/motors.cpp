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
pros::Motor backLeft(20, true);
pros::Motor midLeft(19, true);
pros::Motor frontLeft(18, true);

pros::Motor backRight(2);
pros::Motor midRight(3);
pros::Motor frontRight(12);