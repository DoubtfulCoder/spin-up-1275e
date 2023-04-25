#include "main.h"
#include "1275.h"

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