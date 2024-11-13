#include "StringHelper.h"

std::vector<std::string> base::Split(std::string const &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(str);
    std::string token;

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}
