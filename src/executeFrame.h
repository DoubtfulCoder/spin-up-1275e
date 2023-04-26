#include "main.h"
#include "1275.h"
#include "lib/controller.h"

const double FLYWHEEL_SPEED_PERCENT = 0.46;

struct statefulValues
{
  bool currently_shooting;
  bool currently_indexing;
  bool currently_intaking;
  bool slow_speed;
  bool expansion_value;
  bool indexer_value;
  bool left_arrow_pressed;
};

void executeFrame(ControllerState state, statefulValues lastState);