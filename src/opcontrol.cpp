#include "main.h"
#include "1275.h"
#include "executeFrame.h"
#include "recorder/getControllerState.h"
#include "lib/saves/getBindings.h"
#include "lib/replay/encodeControllerState.h"
#include "lib/util/toBase64.h"
#include "lib/saves/writeRunfile.h"
#include "lib/saves/writeBindings.h"

const int MinuteTicks = (60 * 1000) / 20;

/**
 * Opcontrol
 * Original: doubtfulguy
 * Refactored: piman51277
 */
void opcontrol()
{
  // read in the bindings
  std::map<std::string, std::string> bindings = getBindings();
  int nextId = std::stoi(bindings["nextId"]);
  std::vector<std::string> encodedRun;

  // write to controller what the next run ID will be
  master.set_text(1, 0, "Recording Id: " + std::to_string(nextId));
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  expansion1.set_value(false);
  expansion2.set_value(false);

  // main op loop
  bool hasDumped = false;
  int tick = 0;
  int timeLastFrame = pros::millis();
  while (true)
  {
    // get controller state
    ControllerState state = getControllerState();

    // execute frame
    executeFrame(state);

    // dump run when all bumpers are pressed OR 1 minute has passed
    bool allBumpers = state.L1 && state.L2 && state.R1 && state.R2;

    if (!hasDumped)
    {

      if (tick < MinuteTicks)
      {
        // save the state for recording
        std::bitset<44> stateBits = encodeControllerState(state);
        std::string encodedString = toBase64(stateBits);
        encodedRun.push_back(encodedString);

        printf("Frame %d: %s\n", tick, encodedString.c_str());
      }

      // dump run
      if (allBumpers || tick >= MinuteTicks)
      {
        printf("Dumping run...\n");

        std::string runname = "run" + std::to_string(nextId) + ".txt";
        writeRunfile(encodedRun, runname);
        hasDumped = true;

        // update bindings
        bindings["nextId"] = std::to_string(nextId + 1);
        writeBindings(bindings);

        printf("Run dumped to %s\n", runname.c_str());

        // update controller
        master.set_text(1, 0, "Recording Saved");
      }
    }

    // delay to keep loop at 20ms
    int timeNow = pros::millis();
    int timeSinceLastFrame = timeNow - timeLastFrame;
    int timeToDelay = 20 - timeSinceLastFrame;
    if (timeToDelay > 0)
    {
      pros::delay(timeToDelay);
    }
    timeLastFrame = pros::millis();
    tick++;
  }
}