#include "getControllerState.h"

ControllerState getControllerState()
{
  ControllerState state;
  state.left.x = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  state.left.y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  state.right.x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  state.right.y = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  state.UP = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  state.DOWN = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  state.LEFT = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  state.RIGHT = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  state.A = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
  state.B = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  state.X = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  state.Y = master.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  state.L1 = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  state.L2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  state.R1 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  state.R2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  return state;
}