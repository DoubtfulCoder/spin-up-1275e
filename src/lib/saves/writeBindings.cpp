#include "writeBindings.h"

void writeBindings(std::map<std::string, std::string> bindings)
{
  std::ofstream bindingFile;
  bindingFile.open("/usd/bindings.txt");
  for (auto const &binding : bindings)
  {
    bindingFile << binding.first << "=" << binding.second << std::endl;
  }
  bindingFile.close();
}