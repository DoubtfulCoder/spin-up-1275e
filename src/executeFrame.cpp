#include "executeFrame.h"

void executeFrame(ControllerState state)
{

  bool slowSpeedEnabled = false;

  // Drive control

  // if left stick is active
  int joyX, joyY;
  if (std::abs(state.left.x) > 10 || std::abs(state.left.y) > 10)
  {
    joyX = state.left.x;
    joyY = state.left.y;
  }
  else
  {
    joyX = state.right.x;
    joyY = state.right.y * -1;
  }

  // get joystick values

  // deadzone n<20
  joyX = std::abs(joyX) < 10 ? 0 : joyX * 0.4;
  joyY = std::abs(joyY) < 10 ? 0 : joyY;

  // applies a power curve while preserving direction
  joyY = (joyX != 0 ? 0.4 : 1) * joyY;

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
  if (state.A)
  {
    intake.move(-127);
  }
  else if (state.R2)
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
    expansion1.set_value(true);
    expansion2.set_value(true);
  }
  else
  {
    expansion1.set_value(false);
    expansion2.set_value(false);
  }
}