#include "main.h"
#include "../lib/controller.h"

class Controller
{
  pros::Controller raw;
  ControllerState getState();
  Controller(pros::controller_id_e_t id, bool master);
};
