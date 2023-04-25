#include "getBindings.h"

std::map<std::string, std::string> getBindings()
{
  std::map<std::string, std::string> bindings;
  std::ifstream bindingsFile("/usd/bindings.txt");

  if (bindingsFile.is_open())
  {
    std::string line;
    while (std::getline(bindingsFile, line))
    {
      // split the strings on the = char
      int delimPos = line.find("=");
      std::string label = line.substr(0, delimPos);
      std::string file = line.substr(delimPos + 1);

      bindings[label] = file;
    }
  }

  return bindings;
}