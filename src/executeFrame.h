#include "main.h"
#include "1275.h"
#include "lib/controller.h"

const float FLYWHEEL_IDLE = 0 * -200;
const float FLYWHEEL_SHOOT = 0.65 * -200;
const float FLYWHEEL_MAX = 1.0 * -200;

void executeFrame(ControllerState state);