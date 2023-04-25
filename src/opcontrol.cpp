#include "main.h"
#include "1275.h"
#include "executeFrame.h"
#include "recorder/getControllerState.h"

/**
 * Opcontrol
 * Original: doubtfulguy
 * Refactored: piman51277
 */
void opcontrol()
{
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);


  // main op loop
  int timeLastFrame = pros::millis();
  while (true)
  {

    // get controller state
    ControllerState state = getControllerState();

    // execute frame
    executeFrame(state);

    // delay to keep loop at 50Hz
    int timeNow = pros::millis();
    int timeSinceLastFrame = timeNow - timeLastFrame;
    int timeToDelay = 20 - timeSinceLastFrame;
    if (timeToDelay > 0)
    {
      pros::delay(timeToDelay);
    }
    timeLastFrame = timeNow;
  }
}