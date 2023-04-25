#include "Controller.h"

Controller::Controller(pros::controller_id_e_t id, bool master) : raw(id){};

ControllerState Controller::getState()
{
  ControllerState state;
  state.left.x = raw.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  state.left.y = raw.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  state.right.x = raw.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  state.right.y = raw.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  state.UP = raw.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
  state.DOWN = raw.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  state.LEFT = raw.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
  state.RIGHT = raw.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
  state.A = raw.get_digital(pros::E_CONTROLLER_DIGITAL_A);
  state.B = raw.get_digital(pros::E_CONTROLLER_DIGITAL_B);
  state.X = raw.get_digital(pros::E_CONTROLLER_DIGITAL_X);
  state.Y = raw.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
  state.L1 = raw.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
  state.L2 = raw.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
  state.R1 = raw.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  state.R2 = raw.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  return state;
}