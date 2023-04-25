#include "writeRunfile.h"


void writeRunfile(std::vector<std::string> encodedStates, std::string fileName){
  std::ofstream runfile;
  runfile.open("/usd/"+fileName);
  for(std::string state : encodedStates){
    runfile << state << std::endl;
  }
  runfile.close();
}