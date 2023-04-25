#include "executeFrame.h"

void executeFrame(ControllerState state)
{

  bool slowSpeedEnabled = false;

  // Drive control

  // get joystick values
  int joyX = state.left.x;
  int joyY = state.left.y;

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
  slowSpeedEnabled = state.L2;

  // flywheel speed control
  if (state.R1)
  {
    flywheel.move(FLYWHEEL_MAX);
  }
  else if (state.L1)
  {
    flywheel.move(FLYWHEEL_SHOOT);
  }
  else
  {
    flywheel.move(FLYWHEEL_IDLE);
  }

  // intake control
  if (state.R2)
  {
    intake.move(-127);
  }
  else if (state.A)
  {
    intake.move(100);
  }
  else
  {
    intake.move(0);
  }

  // expansion
  if (state.LEFT && state.RIGHT)
  {
    expansion1.set_value(false);
    expansion2.set_value(false);
  }
}