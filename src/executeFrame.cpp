#include "executeFrame.h"

void executeFrame(ControllerState state)
{

  bool slowSpeedEnabled = false;

  // Drive control

  // if left stick is active
  float joyX, joyY;
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

  // slow speed
  slowSpeedEnabled = state.L2;

  // compute motor power
  float slowSpeedMultipler = slowSpeedEnabled ? 0.5 : 1.0;
  int leftSidePower = slowSpeedMultipler * (joyY + joyX);
  int rightSidePower = slowSpeedMultipler * (joyY - joyX);

  // set motor power
  frontLeft.move_velocity(leftSidePower);
  backLeft.move_velocity(leftSidePower);
  midLeft.move_velocity(leftSidePower);
  frontRight.move_velocity(rightSidePower);
  backRight.move_velocity(rightSidePower);
  midRight.move_velocity(rightSidePower);

  // flywheel speed control
  if (state.R1)
  {
    intake.move_velocity(175);
    flywheel.move_velocity(FLYWHEEL_MAX);
  }
  else if (state.A)
  {
    flywheel.move_velocity(FLYWHEEL_SHOOT);
  }
  else
  {
    flywheel.move_velocity(FLYWHEEL_IDLE);
  }

  // intake control
  if (state.R2)
  {
    intake.move_velocity(-127);
  }
  else if(!state.R1)
  {
    intake.move_velocity(0);
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