#include "main.h"




/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////




const int DRIVE_SPEED = 80; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
// const int TURN_SPEED  = 90;
const int TURN_SPEED  = 60;
const int SWING_SPEED = 90;






///
// Constants
///


// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.


void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}




void turn(int degrees) {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0

  chassis.set_turn_pid(degrees, TURN_SPEED);
  chassis.wait_drive();
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches




  // chassis.set_drive_pid(24, DRIVE_SPEED, true);
  // chassis.wait_drive();


  // chassis.set_drive_pid(-12, DRIVE_SPEED);
  // chassis.wait_drive();


  // chassis.set_drive_pid(2, DRIVE_SPEED);
  // chassis.wait_drive();


  // chassis.set_turn_pid(86, TURN_SPEED);
  // chassis.wait_drive();


  // chassis.set_drive_pid(18, DRIVE_SPEED);
  // chassis.wait_drive();


  // pros::delay(2000);


  flywheel.move_velocity(-0.45 * 200);


  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-9, TURN_SPEED);
  // chassis.wait_drive();
  turn(-11);


  pros::delay(1750);


  intake.move_velocity(25);  

  flywheel.move_velocity(-0.45 * 200);



  pros::delay(2000);


  intake.move_velocity(0);


  // chassis.set_turn_pid(9, TURN_SPEED);
  // chassis.wait_drive();
  turn(11);


  chassis.set_drive_pid(-22, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-90);


  // hit the wall for self correct
  chassis.set_drive_pid(-5.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.set_drive_pid(1.25, DRIVE_SPEED);
  chassis.wait_drive();


  // 3 one-second intervals of intake
  for (int i = 0; i < 3; i++) {
    intake.move_velocity(-200);
    pros::delay(800);
    intake.move_velocity(0);
    pros::delay(10);
  }


  intake.move_velocity(-200);


  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();
  turn(90);


  // chassis.set_drive_pid(-1, DRIVE_SPEED);
  // chassis.wait_drive();


  chassis.set_drive_pid(23, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(-11, TURN_SPEED);
  // chassis.wait_drive();

  turn(-11);


  intake.move_velocity(23);


  // temporarily move flywheel to max speed
  flywheel.move_velocity(-1 * 200);


  pros::delay(2000);

  chassis.set_drive_pid(-3, DRIVE_SPEED);

  pros::delay(750);



  flywheel.move_velocity(-0.45 * 200);


  intake.move_velocity(0);


  // chassis.set_turn_pid(9, TURN_SPEED);
  // chassis.wait_drive();
  turn(11);

  chassis.set_drive_pid(-19.25, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();

  turn(-90);


  // hit the wall for self correct
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.set_drive_pid(1.25, DRIVE_SPEED);
  chassis.wait_drive();


  // 3 one-second intervals of intake
  for (int i = 0; i < 3; i++) {
    intake.move_velocity(-200);
    pros::delay(800);
    intake.move_velocity(0);
    pros::delay(10);
  }


  intake.move_velocity(-200);


  chassis.set_drive_pid(1.25, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  turn(90);


  // chassis.set_drive_pid(-1, DRIVE_SPEED);
  // chassis.wait_drive();


  // finish intaking


  chassis.set_drive_pid(27.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(-17, TURN_SPEED);
  // chassis.wait_drive();

  turn(-19);


  intake.move_velocity(20);


  // temporarily move flywheel to max speed
  flywheel.move_velocity(-1 * 200);


  pros::delay(2000);

  chassis.set_drive_pid(-3.5, DRIVE_SPEED);

  pros::delay(500);


  flywheel.move_velocity(0);


  intake.move_velocity(0);


  // moves back to bottom right roller and intakes the last match load and bottom most disk


  // chassis.set_turn_pid(9, TURN_SPEED);
  // chassis.wait_drive();
  turn(24);


  intake.move_velocity(-200);


  chassis.set_drive_pid(-74, DRIVE_SPEED); //prolly way off
  chassis.wait_drive();


  intake.move_velocity(0);


  chassis.set_drive_pid(-7, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  // turn(-94);


  //chassis.set_drive_pid(-3, DRIVE_SPEED);
  //chassis.wait_drive();


  //spins roller


  intake.move_velocity(-150);


  pros::delay(400);


  intake.move_velocity(0);


  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-95);


  flywheel.move_velocity(-0.45 * 200);


  chassis.set_drive_pid(-12, DRIVE_SPEED); //this is prolly way off
  chassis.wait_drive();


  intake.move_velocity(-150);


  pros::delay(400);


  intake.move_velocity(0);


  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-92, TURN_SPEED);
  // chassis.wait_drive();
  turn(-8);


  chassis.set_drive_pid(73, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(7, TURN_SPEED);
  // chassis.wait_drive();
  turn(21);


  //shoots the hopefully 2 disks


  intake.move_velocity(30);
 
  pros::delay(1250);


  // chassis.set_turn_pid(-5, TURN_SPEED);  //reorientates to facing left
  // chassis.wait_drive();
  turn(-11);


  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-60, TURN_SPEED);
  // chassis.wait_drive();
  turn(-60);


  chassis.set_drive_pid(-8, DRIVE_SPEED);
  chassis.wait_drive();


  intake.move_velocity(-200);


  chassis.set_drive_pid(-13, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-75, TURN_SPEED);
  // chassis.wait_drive();
  turn(-75);


  chassis.set_drive_pid(-30, 35); //moves slowly back while intaking 2 disks
  chassis.wait_drive();


  // chassis.set_turn_pid(105, TURN_SPEED);
  // chassis.wait_drive();
  turn(105);


  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-90);


  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-5, TURN_SPEED);
  // chassis.wait_drive();
  turn(-5);


  intake.move_velocity(20);


  // temporarily move flywheel to max speed
  flywheel.move_velocity(-1 * 200);


  pros::delay(2500);


  flywheel.move_velocity(-0.45 * 200);


  intake.move_velocity(0); //shoots the 3 disks intaked


  // chassis.set_turn_pid(5, TURN_SPEED);
  // chassis.wait_drive();
  turn(5);


  chassis.set_drive_pid(-22.15, DRIVE_SPEED); //goes to other side match loader and repeats code
  chassis.wait_drive();


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-90);


  // hit the wall for self correct
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.set_drive_pid(1.5, DRIVE_SPEED);
  chassis.wait_drive();


  // 3 one-second intervals of intake
  for (int i = 0; i < 3; i++) {
    intake.move_velocity(-200);
    pros::delay(800);
    intake.move_velocity(0);
    pros::delay(10);
  }


  intake.move_velocity(-200);


  chassis.set_drive_pid(2.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();

  turn(90);


  // chassis.set_drive_pid(-1, DRIVE_SPEED);
  // chassis.wait_drive();


  chassis.set_drive_pid(19.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(-5, TURN_SPEED);
  // chassis.wait_drive();

  turn(-5);


  intake.move_velocity(20);


  // temporarily move flywheel to max speed
  flywheel.move_velocity(-1 * 200);


  pros::delay(2500);


  flywheel.move_velocity(-0.45 * 200);


  intake.move_velocity(0);


  // chassis.set_turn_pid(5, TURN_SPEED);
  // chassis.wait_drive();
  turn(5);


  chassis.set_drive_pid(-19.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-90);
  


  // hit the wall for self correct
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.set_drive_pid(1.5, DRIVE_SPEED);
  chassis.wait_drive();


  // 3 one-second intervals of intake
  for (int i = 0; i < 3; i++) {
    intake.move_velocity(-200);
    pros::delay(800);
    intake.move_velocity(0);
    pros::delay(10);
  }


  intake.move_velocity(-200);


  chassis.set_drive_pid(0.75, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();


  // chassis.set_drive_pid(-1, DRIVE_SPEED);
  // chassis.wait_drive();


  // finish intaking


  chassis.set_drive_pid(19.5, DRIVE_SPEED);
  chassis.wait_drive();


  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0


  chassis.set_turn_pid(-5, TURN_SPEED);
  chassis.wait_drive();


  intake.move_velocity(20);


  // temporarily move flywheel to max speed
  flywheel.move_velocity(-1 * 200);


  pros::delay(2500);


  flywheel.move_velocity(0);


  intake.move_velocity(0);


  // chassis.set_turn_pid(5, TURN_SPEED);
  // chassis.wait_drive();
  turn(5);

  chassis.set_drive_pid(-50, DRIVE_SPEED); //prolly way off
  chassis.wait_drive();


  // chassis.set_turn_pid(-90, TURN_SPEED);
  // chassis.wait_drive();
  turn(-90);


  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();


  //spins roller


  intake.move_velocity(-75);


  pros::delay(400);


  intake.move_velocity(0);


  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();
  turn(90);


  chassis.set_drive_pid(-8, DRIVE_SPEED); //this is prolly way off
  chassis.wait_drive();


  intake.move_velocity(-75);


  pros::delay(400);


  intake.move_velocity(0);


  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();


  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();
  turn(-45);


  //expansion...






























 


















  // chassis.set_turn_pid(45, TURN_SPEED);
  // chassis.wait_drive();


  // chassis.set_turn_pid(0, TURN_SPEED);
  // chassis.wait_drive();
}






///
// Turn Example
///
void turn_example() {
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
void drive_and_turn() {
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
void wait_until_change_speed() {
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
void swing_example() {
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
void combining_movements() {
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
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();


    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}


// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();


 if (chassis.interfered) {
   tug(3);
   return;
 }


 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}






// . . .
// Make your own autonomous functions here!
// . . .



// #include "main.h"


// /////
// // For instalattion, upgrading, documentations and tutorials, check out website!
// // https://ez-robotics.github.io/EZ-Template/
// /////


// const int DRIVE_SPEED = 80; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
//                              // If this is 127 and the robot tries to heading correct, it's only correcting by
//                              // making one side slower.  When this is 87%, it's correcting by making one side
//                              // faster and one side slower, giving better heading correction.
// // const int TURN_SPEED  = 90;
// const int TURN_SPEED  = 60;
// const int SWING_SPEED = 90;



// ///
// // Constants
// ///

// // It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// // If the objects are light or the cog doesn't change much, then there isn't a concern here.

// void default_constants() {
//   chassis.set_slew_min_power(80, 80);
//   chassis.set_slew_distance(7, 7);
//   chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
//   chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
//   chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
// }

// void one_mogo_constants() {
//   chassis.set_slew_min_power(80, 80);
//   chassis.set_slew_distance(7, 7);
//   chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
//   chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
//   chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
// }

// void two_mogo_constants() {
//   chassis.set_slew_min_power(80, 80);
//   chassis.set_slew_distance(7, 7);
//   chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
//   chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
//   chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
//   chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
// }

// void exit_condition_defaults() {
//   chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
//   chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
//   chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
// }

// void modified_exit_condition() {
//   chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
//   chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
//   chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
// }



// ///
// // Drive Example
// ///
// void drive_example() {
//   // The first parameter is target inches
//   // The second parameter is max speed the robot will drive at
//   // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
//   // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


//   // chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   // chassis.wait_drive();

//   // chassis.set_drive_pid(-12, DRIVE_SPEED);
//   // chassis.wait_drive();

//   // chassis.set_drive_pid(2, DRIVE_SPEED);
//   // chassis.wait_drive();

//   // chassis.set_turn_pid(86, TURN_SPEED);
//   // chassis.wait_drive();

//   // chassis.set_drive_pid(18, DRIVE_SPEED);
//   // chassis.wait_drive();

//   // pros::delay(2000);

//   // flywheel.move_velocity(-0.45 * 200);

//   chassis.set_drive_pid(6, DRIVE_SPEED);
//   chassis.wait_drive();

//   pros::delay(2000);

//   intake.move_velocity(30);  

//   pros::delay(2000);

//   intake.move_velocity(0);

//   chassis.set_drive_pid(-22.25, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(-87, TURN_SPEED);
//   chassis.wait_drive();

//   // hit the wall for self correct
//   chassis.set_drive_pid(-3.5, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(1.25, DRIVE_SPEED);
//   chassis.wait_drive();

//   // 3 one-second intervals of intake
//   for (int i = 0; i < 3; i++) {
//     intake.move_velocity(-200);
//     pros::delay(1000);
//     intake.move_velocity(0);
//     pros::delay(10);
//   }

//   intake.move_velocity(-200);

//   chassis.set_drive_pid(0.75, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.reset_pid_targets(); // Resets PID targets to 0
//   chassis.reset_gyro(); // Reset gyro position to 0
//   chassis.reset_drive_sensor(); // Reset drive sensors to 0

//   chassis.set_turn_pid(90, TURN_SPEED);
//   chassis.wait_drive();

//   // chassis.set_drive_pid(-1, DRIVE_SPEED);
//   // chassis.wait_drive();

//   pros::delay(2200);
//   intake.move_velocity(0);

//   chassis.set_drive_pid(19.5, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.reset_pid_targets(); // Resets PID targets to 0
//   chassis.reset_gyro(); // Reset gyro position to 0
//   chassis.reset_drive_sensor(); // Reset drive sensors to 0

//   chassis.set_turn_pid(-6, TURN_SPEED);
//   chassis.wait_drive();

//   intake.move_velocity(20);

//   // temporarily move flywheel to max speed
//   // flywheel.move_velocity(-1 * 200);

//   pros::delay(3000);

//   // flywheel.move_velocity(-0.45 * 200);

//   intake.move_velocity(0);

//   chassis.set_drive_pid(-19.5, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.reset_pid_targets(); // Resets PID targets to 0
//   chassis.reset_gyro(); // Reset gyro position to 0
//   chassis.reset_drive_sensor(); // Reset drive sensors to 0

//   chassis.set_turn_pid(-86, TURN_SPEED);
//   chassis.wait_drive();

//   // hit the wall for self correct
//   chassis.set_drive_pid(-3.5, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(1.25, DRIVE_SPEED);
//   chassis.wait_drive();

//   // 3 one-second intervals of intake
//   for (int i = 0; i < 3; i++) {
//     intake.move_velocity(-200);
//     pros::delay(800);
//     intake.move_velocity(0);
//     pros::delay(10);
//   }

//   intake.move_velocity(-200);

//   chassis.set_drive_pid(0.75, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.reset_pid_targets(); // Resets PID targets to 0
//   chassis.reset_gyro(); // Reset gyro position to 0
//   chassis.reset_drive_sensor(); // Reset drive sensors to 0

//   chassis.set_turn_pid(90, TURN_SPEED);
//   chassis.wait_drive();

//   // chassis.set_drive_pid(-1, DRIVE_SPEED);
//   // chassis.wait_drive();

//   // finish intaking
//   pros::delay(2200);
//   intake.move_velocity(0);

//   chassis.set_drive_pid(19.5, DRIVE_SPEED);
//   chassis.wait_drive();

//   chassis.reset_pid_targets(); // Resets PID targets to 0
//   chassis.reset_gyro(); // Reset gyro position to 0
//   chassis.reset_drive_sensor(); // Reset drive sensors to 0

//   chassis.set_turn_pid(5, TURN_SPEED);
//   chassis.wait_drive();

//   intake.move_velocity(20);

//   // temporarily move flywheel to max speed
//   // flywheel.move_velocity(-1 * 200);

//   pros::delay(3000);

//   flywheel.move_velocity(-0.45 * 200);

//   intake.move_velocity(0);



//   // chassis.set_turn_pid(45, TURN_SPEED);
//   // chassis.wait_drive();

//   // chassis.set_turn_pid(0, TURN_SPEED);
//   // chassis.wait_drive();
// }



// ///
// // Turn Example
// ///
// void turn_example() {
//   // The first parameter is target degrees
//   // The second parameter is max speed the robot will drive at


//   chassis.set_turn_pid(90, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();
// }



// ///
// // Combining Turn + Drive
// ///
// void drive_and_turn() {
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_drive();
// }



// ///
// // Wait Until and Changing Max Speed
// ///
// void wait_until_change_speed() {
//   // wait_until will wait until the robot gets to a desired position


//   // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_until(6);
//   chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_until(-6);
//   chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
//   chassis.wait_drive();
// }



// ///
// // Swing Example
// ///
// void swing_example() {
//   // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
//   // The second parameter is target degrees
//   // The third parameter is speed of the moving side of the drive


//   chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_until(12);

//   chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
//   chassis.wait_drive();
// }



// ///
// // Auto that tests everything
// ///
// void combining_movements() {
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_drive();
// }



// ///
// // Interference example
// ///
// void tug (int attempts) {
//   for (int i=0; i<attempts-1; i++) {
//     // Attempt to drive backwards
//     printf("i - %i", i);
//     chassis.set_drive_pid(-12, 127);
//     chassis.wait_drive();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.reset_drive_sensor();
//       chassis.set_drive_pid(-2, 20);
//       pros::delay(1000);
//     }
//     // If robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// // If there is no interference, robot will drive forward and turn 90 degrees. 
// // If interfered, robot will drive forward and then attempt to drive backwards. 
// void interfered_example() {
//  chassis.set_drive_pid(24, DRIVE_SPEED, true);
//  chassis.wait_drive();

//  if (chassis.interfered) {
//    tug(3);
//    return;
//  }

//  chassis.set_turn_pid(90, TURN_SPEED);
//  chassis.wait_drive();
// }



// // . . .
// // Make your own autonomous functions here!
// // . . .