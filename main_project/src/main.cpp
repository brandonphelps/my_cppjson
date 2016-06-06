

#include <iostream>
#include <fstream>
#include <vector>

#include "json_parser.h"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "Please provide a filename" << std::endl;
  }
  else
  {
    JsonParser p;
    
    std::map<std::string, std::string> configFile = p.parse(argv[1]);

    std::cout << "file contents" << std::endl;

    std::cout << "project url: " << configFile["project url"] << std::endl;

    for(std::map<std::string, std::string>::iterator it = configFile.begin(); it != configFile.end(); ++it)
    {
      std::cout << it->first << " : " << it->second << std::endl;
    }
  }
  return 0;
}
