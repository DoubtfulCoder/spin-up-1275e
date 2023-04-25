#include "readRunfile.h"

std::vector<std::string> readRunfile(std::string fileName)
{
  std::vector<std::string> states;
  std::ifstream runFile("/usd/" + fileName);

  if (runFile.is_open())
  {
    std::string line;
    while (std::getline(runFile, line))
    {
      states.push_back(line);
    }
  }

  return states;
}