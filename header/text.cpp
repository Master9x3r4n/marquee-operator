#include "text.h"

#include <sstream>

std::vector<std::string> getArgs(std::string input)
{
    std::vector<std::string> args;
    std::string word = "";
    std::istringstream stream(input);

    while (stream >> word)
        args.push_back(word);

    return args;
}