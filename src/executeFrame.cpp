#include "executeFrame.h"

void executeFrame(ControllerState state, statefulValues &lastState)
{

  double x = state.left.x;
  double y = state.right.y;

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
  if (state.L2)
  {
    lastState.slow_speed = true;
  }
  else
  {
    lastState.slow_speed = false;
  }

  double multiplier = 1.0;
  if (lastState.slow_speed)
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
  if (state.A)
  {
    if (lastState.currently_shooting)
    {
      flywheel.move_velocity(0);
      lastState.currently_shooting = false;
      printf("This was triggered!\n");
    }
    else
    {
      flywheel.move_velocity(FLYWHEEL_SPEED_PERCENT * -200);
      lastState.currently_shooting = true;

      printf("This was triggered 1\n!");
    }
    pros::delay(300);
  }

  printf("Flywheel vel: %d\n", flywheel.get_actual_velocity());

  // intake
  if (state.R2)
  {
    intake.move_velocity(-200);
  }
  else if (state.L1)
  {
    // roller
    intake.move_velocity(200);
  }
  else if (state.R1)
  {
    // indexer
    lastState.currently_indexing = true;
    intake.move_velocity(25);
    flywheel.move_velocity(-1 * 200); // move flywheel up to max power
  }
  else
  {
    intake.move_velocity(0);
    if (lastState.currently_indexing)
    {
      lastState.currently_indexing = false;
      flywheel.move_velocity(FLYWHEEL_SPEED_PERCENT * -200); // move back to normal speed
    }
  }

  // expansion shift key
  if (state.LEFT)
  {
    // shift key for not accidentally activating expansion
    lastState.left_arrow_pressed = true;
  }
  // actual expansion
  if (state.RIGHT && lastState.left_arrow_pressed)
  {
    // if (state.LEFT)) {
    // expansion_value = !expansion_value;
    expansion1.set_value(true);
    expansion2.set_value(true);
    pros::delay(3000);
  }
}