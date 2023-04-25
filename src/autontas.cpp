#include "main.h"
#include "1275.h"
#include "executeFrame.h"
#include "lib/saves/getBindings.h"
#include "lib/replay/decodeControllerState.h"
#include "lib/util/fromBase64.h"
#include "lib/util/toBase64.h"
#include "lib/saves/readRunfile.h"

void printBitset(std::bitset<44> bits)
{
  std::string k;
  for (int i = 0; i < 44; i++)
  {
    k += std::to_string(bits[i]);
  }
  printf("%s\n", k.c_str());
}

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
  printf("Verify success!");

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
    int timeToWait = 20 - timeElapsed;
    if (timeToWait > 0)
    {
      pros::delay(timeToWait);
    }
    timeLastFrame = pros::millis();

    // increment tick
    tick++;
  }

  // set last tick to do nothing
  ControllerState stop = {};
  executeFrame(stop);
}