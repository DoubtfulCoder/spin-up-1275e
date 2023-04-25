#include "main.h"
#include "1275.h"
#include "executeFrame.h"
#include "lib/saves/getBindings.h"
#include "lib/replay/decodeControllerState.h"
#include "lib/util/fromBase64.h"
#include "lib/saves/readRunfile.h"

void autontas()
{
  // read in the bindings
  std::map<std::string, std::string> bindings = getBindings();

  // figure out which run is "autontas"
  std::string autontasId = bindings["autontas"];

  // let the user know what's going on
  master.set_text(1, 0, "Exec TAS " + autontasId);

  // read and parse the run file
  std::vector<std::string> encodedRun = readRunfile(autontasId);
  std::vector<ControllerState> run;

  // decode the run
  for (std::string encodedState : encodedRun)
  {
    std::bitset<44> stateBits = fromBase64(encodedState);
    ControllerState state = decodeControllerState(stateBits);
    run.push_back(state);
  }

  // execute the run
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  expansion1.set_value(false);
  expansion2.set_value(false);

  int tick = 0;
  int timeLastFrame = pros::millis();
  while (tick < run.size())
  {
    // get controller state
    ControllerState state = run[tick];

    // execute frame
    executeFrame(state);

    // print frame
    printf("Frame %d: %s\n", tick, encodedRun[tick].c_str());

    // wait for next frame
    int timeNow = pros::millis();
    int timeElapsed = timeNow - timeLastFrame;
    int timeToWait = 50 - timeElapsed;
    if (timeToWait > 0)
    {
      pros::delay(timeToWait);
    }
    timeLastFrame = pros::millis();

    // increment tick
    tick++;
  }
}